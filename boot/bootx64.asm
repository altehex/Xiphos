	format	PE64 DLL EFI
	entry	__entry
<<<<<<< HEAD
	
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
=======

include "../include/uefi.inc"	

	
section		'.text' code executable readable
	
	use64
__entry:
	EFI_INIT
	jc		@f

	
	
@@:				  
	EFI_CALL conOut,				\	
			 EfiTextOutProtocol.output_string, 	\ 
			 conOut, errorMsg
	
	mov		EAX, EFI_SUCCESS
	ret

	
section 	'.data' data readable writeable

errorMsg	du	"An error occured.", 13, 10, 0
>>>>>>> bootloader2
