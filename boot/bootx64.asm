	format	PE64 DLL EFI
	entry	__entry

include "../include/uefi.inc"

;; include "../firmware/uefi/video_mode.asm" 

	
section		'.text' code executable readable
	
	use64
__entry:
	EFI_INIT			; CF = 1 if an error occured.
	jc		__error
	
	EFI_CALL	conOut, EfiTextOut.clear_scr, 1, conOut
					  
	EFI_CALL 	conOut, EfiTextOut.output_string, 2,	\ 
				conOut, startupMsg

;;----------------------
;; TODO: Get ACPI table address
;;---------------------

	EFI_CALL	bs, EfiBootServices.locate_protocol, 3,	\
	 			EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID,		\
	 			NULL, efiGraphicsOut
	
__error:				  
	EFI_CALL 	conOut, EfiTextOut.output_string, 2,	\ 
				conOut, errorMsg
	
	mov		EAX, EFI_SUCCESS
	ret

	
section 	'.data' data readable writeable

;; Protocol table
efiGraphicsOut	rq	1
	
;; String table
startupMsg  du  "Starting up ThanatOS...", 13, 10, 0
errorMsg	du	"An error occured.", 13, 10, 0
