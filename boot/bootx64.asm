	format	PE64 DLL EFI
	stack	STACK_SIZE
	entry	__entry
	
include "../include/uefi.inc"
include "../include/types.inc"
	
	
MEMMAP_SZ   equ 65536

	
section		'.text'		code executable readable
	
	use64
__entry:
	EFI_INIT	imgHandle, sysTable
	jc		__error
	
	__eficall	EfiTextOut, clear_scr, EfiTextOut
					  
	__eficall 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, startupMsg

;;----------------------
;; TODO: Get ACPI table address
;;---------------------
;; Set up video (the snippet is inlined)
include "../firmware/uefi/asm/video.asm"

;; Get the file interface
	__eficall	EfiBootServices, locate_protocol, 		\
				EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,	\
				NULL, EfiFileSystem

	__eficall	EfiFileSystem, open_vol,	\
				EfiFileSystem, EfiFile
	
;; Load the kernel to RAM
load_kernel:	
	__eficall	EfiFile, open,			\
				[EfiFile], imgFileHandle, imgPath,	\
				EFI_FILE_MODE_READ,	0	

_sub_EfiFile 	equ imgFileHandle
	
	cmp		RAX, EFI_NOT_FOUND
	jne		@f			
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, imgNotFoundMsg
	jmp		$

@@:
	test	EAX, EAX
	jnz		.error

@@:
	mov		RBX, [_sub_EfiFile]
	mov		RCX, RBX
	mov		RBX, [RBX + _EfiFile.read]
	mov		RDX, IMG_SIZE
	mov		R8, IMG_BASE
	
	call	RBX

	test	EAX, EAX
	jz		@f
.error:
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, imgLoadErrorMsg
	jmp		$
	

@@:
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, imgIsLoadedMsg


	mov		RBX, [_sub_EfiFile]
	mov		RCX, RBX
	mov		RBX, [RBX + _EfiFile.close]
	call	RBX

	purge	_sub_EfiFile
	
@@:

	;; jmp		__error

;; Get memory map
	__eficall	EfiBootServices, get_memmap,	\
				memMapSz, memMap, memMapKey,	\
				memMapDescSz, memMapDescVer

;; Exit EFI
	__eficall	EfiBootServices, exit_bs,	\
				[imgHandle], [memMapKey]
	test		RAX, RAX
	jnz 	__error	  
	
	push	IMG_BASE
	ret
	
	use64
__error:			
	__eficall 	EfiTextOut, output_string, 	\ 
 				EfiTextOut, errorMsg
	xor		EAX, EAX	; EFI_SUCCESS
	ret					

	
section		'.rodata'	data readable

memMapSz		dq	MEMMAP_SZ
	
;; String table
;;-------------------------------------------
imgPath			du	IMG_PATH, 0
	
startupMsg  	du  "Starting up ", IMG_NAME, "...", 13, 10, \
					"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-*", 13, 10, 0
imgIsLoadedMsg	du	"[ ** ] Loaded OS image at ", IMG_BASE_QUOTED, 13, 10, 0

;; Error messages
errorMsg		du	"[ !! ] An error occured.", 13, 10, 0
imgNotFoundMsg	du	"[ !! ] OS image is not present.", 13, 10, 0
imgLoadErrorMsg du	"[ !! ] Failed to load the OS image", 13, 10, 0
	
;; UUID table
EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID:		_EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID:	_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID

	
section 	'.bss'		data readable writeable discardable
	
imgHandle		PTR
sysTable		PTR
return			PTR

;; Protocol table
EfiGraphicsOut	PTR
EfiFileSystem	PTR
EfiFile			PTR

imgFileHandle	PTR
	
;; Memory map
memMap			EfiMemoryDescriptor
memMapKey		IN
memMapDescSz	IN
memMapDescVer	I32

	
section		'.reloc'	fixups data discardable

