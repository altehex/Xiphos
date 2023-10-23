;; WIP. New tables will be added if they're needed

;; ......

	xor		RAX, RAX
	mov		[acpiTablesBase], RAX
	
;; Get ACPI table address
	mov		RAX, [sysTable] 					 ; ->sysTable
	mov		RCX, [RAX + EfiSystemTable.entryNum] ; ->sysTable->num
	mov		RAX, [RAX + EfiSystemTable.conf] 	 ; ->sysTable->conf
	dec		RCX
	mov		RBX, qword [EFI_RSDP_GUID] 	; *EFI_ACPI_TABLE_GUID

@@:
	;; RSI = ->sysTable->conf + EfiConftable_ENTRY_SZ * n
	cmp		RBX, [RAX]
	je		@f

	add		RAX, EfiConfTable_ENTRY_SZ
	loop	@b

@@:	
	;; Copy RSDP address
	mov		RAX, [RAX + EfiConfTable.table]
	xor		RBX, RBX
	mov		[RBX], RAX

	add		RBX, 8
	and		BL, 0xF8

	mov		[memMapBase], RBX
	mov		[acpiTablesSz], RBX
	
;; But it gotta copy the entire RSDP, XSDT et al.
	
;; Make sure to accumulate the size of tables in acpitTablesSz
;; It's important to make a proper memory map

;; ......
