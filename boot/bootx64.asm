	format	PE64 DLL EFI
	entry	__entry
	
include "../include/uefi.inc"

section		'.text' code executable readable
	
	use64
;; ----------------------
__entry:
	EFI_INIT imgHandle, 	\
			 sysTable,		\
			 return
	jc		@f
	
	mov		RAX, [sysTable]
	mov		RAX, [RAX + EFI_BOOT_SERVICES]
	mov		[bootServices], RAX

	mov		RAX, [sysTable]

@@:
	mov		EAX, EFI_SUCCESS
	ret

section 	'.data' data readable writeable
	
imgHandle:		dq 	0
sysTable:		dq 	0
return:			dq  0
bootServices	dq	0

section '.reloc' fixups data discardable
