	format	PE64 DLL EFI
	entry	__entry

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
