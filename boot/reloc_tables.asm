;; WIP. New tables will be added if the're needed

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
	;; Copy RSDP address to 0x00000000
	mov		RAX, [RAX + EfiConfTable.table]
	mov		[qword RSDP], RAX

;; Copy every needed table
