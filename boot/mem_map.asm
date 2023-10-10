include "../include/boot/mem_map.inc"
	
;; ......
	
	lea		RCX, [memMapSz]
	lea		RDX, [memMap]
	lea		R8, [memMapKey]
	lea		R9, [memMapDescSz]
	__eficall	EfiBootServices, get_memmap,	\
				RCX, RDX, R8, R9, memMapDescVer

;; parse EFI memory descriptors
;; TO-DO: merge regions of the same type to shrink the table
;; TO-DO 2: parse ACPI regions according to the memory layout and size of all tables(acpiTablesSz)
	
;; RAX: EFI memory map descriptor
	lea		RAX, [memMap]
;; RBX: EFI memory descriptor size
	mov		RBX, [memMapDescSz]
;; RCX: Last EFI memory map descriptor
	mov		RCX, RAX
	add		RCX, [memMapSz]
	sub		RCX, RBX
;; RDX:	Our memory records
	mov		RDX, MEM_MAP_BASE + memHeader.rec
	
	jmp		@f

;; R8D: memory region type
;; R8: memory region base/size
	
parse_mem_map:
	add		RAX, RBX

@@:
	mov		R8D, dword [RAX]
	cmp		R8D, EFI_RTS_DATA
	jg		@f
	mov		R8D, __RESERVED
	jmp		.parse
@@:
	cmp		R8D, EFI_FREE
	jne		@f
	mov		R8D, __RAM
	jmp		.parse
@@:
	cmp		R8D, EFI_UNUSABLE
	jne		@f
	mov		R8D, __UNUSABLE
	jmp		.parse
@@:
	cmp		R8D, EFI_ACPI_RECLAIM
	jne		@f
	mov		R8D, __ACPI_TABLES
	jmp		.parse
@@:
	cmp		R8D, EFI_ACPI_NVS
	jne		@f
	mov		R8D, __ACPI_NVS
	jmp		.parse
@@:
	cmp		R8D, EFI_PERSISTENT
	jne		.default
	mov		R8D, __NON_VOLATILE
	
.parse:
	mov		[RDX], R8D
	add		RDX, memRecord.base
	mov		R8, [RAX + EfiMemoryDescriptor.physStart]
	mov		[RDX], R8
	add		RDX, 8	; memRecord.sz
	mov		R8, [RAX + EfiMemoryDescriptor.numOfPages]
	shl		R8, 12	; Multiply by PAGE_SZ
	mov		[RDX], R8
	
	add 	RDX, 8 	; SIZE_OF memRecord
.default:
	cmp		RAX, RCX
	jne 	parse_mem_map

	sub		RDX, MEM_MAP_BASE + memHeader.rec
	mov		[dword MEM_MAP_BASE + memHeader.sz], RDX	;
	
;; ......
