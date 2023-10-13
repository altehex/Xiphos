include "../include/boot/mem_map.inc"
	
;; ......

;; Get memory map size and descriptor size
 	lea		RCX, [memMapSz]
	xor		R8, R8
	lea		R9, [memMapDescSz]
	__eficall	EfiBootServices, get_memmap,	\
				RCX, [memMap], R8, R9, NULL

	mov		R8, [memMapDescSz]
	add		R8, R8
	add		R8, [memMapSz]
	mov		[memMapSz], R8
	
	xor		RCX, RCX
	add		R8, PAGE_SZ - 1
	shr		R8, 12
	lea		R9, [memMap]
	__eficall	EfiBootServices, alloc_pages,	\
				RCX, EFI_LOADER_DATA, R8, R9
	
	lea		RCX, [memMapSz]
	lea		R8, [memMapKey]
	lea		R9, [memMapDescSz]
	__eficall	EfiBootServices, get_memmap,	\
				RCX, [memMap], R8, R9, memMapDescVer
	
;; RAX: EFI memory map descriptor
	mov		RAX, [memMap]
	
;; RBX: EFI memory descriptor size
	mov		RBX, [memMapDescSz]
	
;; RCX: Last EFI memory map descriptor
	mov		RCX, RAX
	add		RCX, [memMapSz]
	
;; RDX:	Our memory records
	mov		RDX, MEM_MAP_BASE + 4 + 20
;; Reserving 20 bytes for ACPI tables region record

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
	add		RDX, 4
	mov		R9, [RAX + EfiMemoryDescriptor.physStart]
	mov		[RDX], R9
	
	add		RDX, 8	; memRecord.sz
	mov		R9, [RAX + EfiMemoryDescriptor.numOfPages]
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
	mov		[RDX], R9

	add 	RDX, 8
	jmp		@f
	
.default:
	add		RAX, RBX

@@:
	cmp		RAX, RCX
	jne 	parse_mem_map

.done:
;; Load memory map size at the beginning
	sub		RDX, MEM_MAP_BASE + 4
	mov		[dword MEM_MAP_BASE], EDX

;; Load ACPI tables region record at the beginning
	mov		RAX, __RAM
	mov		[dword MEM_MAP_BASE + 4], EAX
	mov		[qword MEM_MAP_BASE + 4 + 4], RAX ; RAX is still zero, as our ACPI region
	;; mov	RAX, [acpiDataSz]
	;; mov	[qword MEM_MAP_BASE+4+12], RAX
    ;; mov  RDX, [qword MEM_MAP_BASE+4+20+4]	; second record offset
	;; add  RDX, RAX
	;; mov	[qword MEM_MAP_BASE+4+20+4], RDX
	;; mov  RDX, [qword MEM_MAP_BASE+4+20+12]	; second record size
	;; sub  RDX, RAX
	;; mov	[qword MEM_MAP_BASE+4+20+12], RDX
	
	mov		RDX, [memMapSz]
	add		RDX, PAGE_SZ - 1
	shr		RDX, 12	
	__eficall	EfiBootServices, free_pages,	\
				[memMap], RDX

;; Now i gotta figure out how to map the entire RAM
	
;; ......
