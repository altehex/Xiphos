	format	PE64 DLL EFI
	entry	__entry

include "../include/uefi.inc"

;; include "../firmware/uefi/video_mode.asm" 

	
section		'.text'		code executable readable
	
	use64
__entry:
	EFI_INIT	imgHandle, sysTable	; CF = 1 if an error occured.
	jc		__error
	
	EFI_CALL	EfiTextOut, clear_scr, EfiTextOut
					  
	EFI_CALL 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, startupMsg

;;----------------------
;; TODO: Get ACPI table address
;;---------------------

;; Get the video interface
	EFI_CALL	EfiBootServices, locate_protocol,	\
				EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 	\
				NULL, EfiGraphicsOut
	
;; Get memory map
	;; EFI_CALL	bs, EfiBootServices.get_memmap, 	\
	
__error:				  
	EFI_CALL 	EfiTextOut, output_string, 	\ 
 				EfiTextOut, errorMsg
	
	mov		EAX, EFI_SUCCESS
	ret

	
section 	'.data'		data readable writeable
	
imgHandle		rq 	1
sysTable		rq 	1
return			rq  1
	
;; Protocol table
EfiGraphicsOut		rq	1
	
;; String table
startupMsg  du  "Starting up ThanatOS...", 13, 10, 0
errorMsg	du	"An error occured.", 13, 10, 0

	
section		'.reloc'	fixups data discardable
