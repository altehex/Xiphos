include "../include/boot/mem_map.inc"
	
;; ......

;; How addresses are passed:
;;------------------------------------*

;;   [acpiTableBase = SYS_TABLES_BASE (0x00)]
;; reloc_tables.asm ----+
;;						|
;;						V  [memMapBase = (acpiTableBase + acpiTablesSz + 8) & 0x...FFF8]
;;					mem_map.asm ----+
;;									|
;;									V [idtBase = (memMapBase + memMapSz + 8) & 0xFFF8]
;;								 int.asm ---+
;; 											|
;;											V [pml4Base = (idtBase + IDT_SZ + 0x1000) & 0x...F000]
;; 	                					paging.asm
	
;; Get memory map size and descriptor size
	xor		R8, R8
	__eficall	EfiBootServices, get_memmap,	\
				memMapSz, [memMap], R8, 		\
				memMapDescSz, NULL

	mov		R8, [memMapDescSz]
	add		R8, [memMapSz]
	mov		[memMapSz], R8
 
	xor		RCX, RCX	; AllocateAnyPages
	add		R8, PAGE_SZ - 1
	shr		R8, 12
	__eficall	EfiBootServices, alloc_pages,	\
				RCX, EFI_LOADER_DATA, R8, memMap
	
	__eficall	EfiBootServices, get_memmap,	\
				memMapSz, [memMap], memMapKey,	\
				memMapDescSz, memMapDescVer
	
;; RAX: EFI memory map descriptor
	mov		RAX, [memMap]
	
;; RBX: EFI memory descriptor size
	mov		RBX, [memMapDescSz]
	
;; RCX: Last EFI memory map descriptor
	mov		RCX, RAX
	add		RCX, [memMapSz]
	
;; RDX:	Our memory records
	mov		RDX, [memMapBase]
	add		RDX, 20 * 2
;; Reserving first 20 bytes for the memory map region
;; Second 20 bytes are for the ACPI tables region record
;; Don't map paging tables region(no need to do it)

;; R8D: memory region type (EFI)
;; R9: memory region type, base or size
;; R10: merge procedure
	
;; Don't map reserved and unusable memory regions(whatever is related to EFI runtime)

parse_mem_map:
	mov		R8D, dword [RAX]
	
	cmp		R8D, EFI_BS_DATA
	jle		@f
	cmp		R8D, EFI_FREE
	je		@f
	cmp		R8D, EFI_ACPI_RECLAIM
	jne		.non_free
@@:
	mov		R10, .free_merge
	mov		R9D, __RAM
	jmp		.parse

.non_free:
	mov		R10, .non_free_merge
	
	cmp		R8D, EFI_ACPI_NVS
	jne		@f
	mov		R9D, __ACPI_NVS
	jmp		.parse
@@:
	cmp		R8D, EFI_PERSISTENT
	jne		.default
	mov		R9D, __NON_VOLATILE
	
.parse:
	mov		[RDX], R9D
	mov		R9, [RAX + EfiMemoryDescriptor.physStart]
	mov		[RDX + 4], R9
	
	mov		R9, qword [RAX + EfiMemoryDescriptor.numOfPages]
.merge:
	add		RAX, RBX
	cmp		RAX, RCX
	je		.done

	jmp		R10

.free_merge:
	mov		R8D, dword [RAX]
	cmp		R8D, EFI_BS_DATA
	jle		.add
	cmp		R8D, EFI_FREE
	je		.add
	cmp		R8D, EFI_ACPI_RECLAIM
	je		.add
	
	jmp		.next_type
	
.non_free_merge:
	cmp		R8D, dword [RAX]
	jne		.next_type
	
.add:
	add		R9, [RAX + EfiMemoryDescriptor.numOfPages]
	jmp		.merge
	
.next_type:
	shl		R9, 12	; Multiply by PAGE_SZ
	mov		[RDX + 4 + 8] , R9

	add 	RDX, 20
	jmp		@f
	
.default:
	add		RAX, RBX

@@:
	cmp		RAX, RCX
	jne 	parse_mem_map

.done:
;; Make memory map region record at the beginning
	mov		RBX, [memMapBase]
	
	mov		dword [RBX], __MEMORY_MAP
	mov		RAX, RBX
	mov		qword [RBX + 4], RAX
	sub		RDX, RAX
	mov		[RBX + 4 + 8], RDX
	
;; Load ACPI tables region record
	mov		dword [RBX], __ACPI_TABLES
	xor		RAX, RAX	; SYS_TABLES_BASE
	mov		qword [RBX + 20 + 4], RAX 
	mov		RAX, [acpiTablesSz]
	mov		qword [RBX + 20 + 4 + 8], RAX
	
;; Fix the base and the size of the first __RAM entry
;; (the first 1 MB is for system data)
	mov		qword [RBX + 20 * 2 + 4], IMG_BASE
	sub		qword [RBX + 20 * 2 + 4 + 8], IMG_BASE
	
	mov		RDX, [memMapSz]
	add		RDX, PAGE_SZ - 1
	shr		RDX, 12	
	__eficall	EfiBootServices, free_pages,	\
				[memMap], RDX

	mov		RAX, [RBX + 4]
	mov		RBX, [RBX + 4 + 8]
	add		RAX, RBX
	add		RAX, 8
	and		AL, 0xF8
	mov		[idtBase], RAX
	mov		[memMapSz], RBX
	
;; ......
