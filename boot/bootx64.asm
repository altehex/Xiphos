	format	PE64 DLL EFI
	stack	STACK_SIZE
	entry	__entry

include "../include/acpi.inc"
include "../include/size.inc"
include "../include/types.inc"
include "../include/boot/uefi.inc"
	
MEM_MAP_SZ  = 65536
	
section		'.text'		code executable readable
	
	use64
__entry:
	EFI_INIT	imgHandle, sysTable
	jc		__error
	
;; Set up video (the snippet is inlined)
include "./video.asm"
					  
	__eficall 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, startupMsg
	
;; Get the loaded image interface
	lea		RDX, [EFI_LOADED_IMAGE_PROTOCOL_GUID]
	lea		R8,	[EfiLoadedImg]
	__eficall	EfiBootServices, hdl_protocol,	\
				[imgHandle], RDX, R8
	
;; Get the file interface
	mov		RCX, [EfiLoadedImg]
	lea		RDX, [EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID]
	lea		R8, [EfiFileSystem]
	__eficall	EfiBootServices, hdl_protocol,			\
				[RCX + _EfiLoadedImg.devHdl], RDX, R8

	lea		RDX, [EfiFile]
	__eficall	EfiFileSystem, open_vol,	\
				EfiFileSystem, RDX
	
;; Load the kernel to RAM
load_kernel:
	lea		RDX, [loadingImgMsg]
	__eficall	EfiTextOut,	output_string,	\
				EfiTextOut, RDX

	lea		RDX, [imgFileHandle]
	lea		R8, [imgPath]
	__eficall	EfiFile, open,			\
				EfiFile, RDX, R8,		\
				EFI_FILE_MODE_READ,	0	
	test	EAX, EAX
	jz		@f			

	cmp		RAX, EFI_NOT_FOUND
	jne		.error
	lea		RDX, [imgNotFoundMsg]
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, RDX

@@:
_sub_EfiFile	equ imgFileHandle

	mov		RBX, [_sub_EfiFile]
	mov		RCX, RBX
	mov		RBX, [RBX + _EfiFile.read]
	lea		RDX, [imgSz]
	mov		R8, IMG_BASE
	call	RBX

	test	RAX, RAX
	jz		@f
	
.error:
	lea		RDX, [imgLoadErrorMsg]
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, RDX
	jmp		$

@@:
	lea		RDX, [imgIsLoadedMsg]
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, RDX

	mov		RBX, [_sub_EfiFile]
	mov		RCX, RBX
	mov		RBX, [RBX + _EfiFile.close]
	call	RBX
	
	purge	_sub_EfiFile

;; System tables relocation 
include "./reloc_tables.asm"
	
;; Get memory map
include "./mem_map.asm"
	
;; Exit EFI
	__eficall	EfiBootServices, exit_bs,	\
				[imgHandle], [memMapKey]
	test		EAX, EAX
	jnz 	__error

;; Load the kernel entry point
	mov		RAX, IMG_BASE + 0x1000
	push	RAX
	ret


	use64
__error:			
	__eficall 	EfiTextOut, output_string, 	\ 
 				EfiTextOut, errorMsg
	xor		RAX, RAX	; EFI_SUCCESS
	ret					

	
section		'.rodata'	data readable

memMapSz		I64	MEM_MAP_SZ
	
;; String table
;;-------------------------------------------
imgPath			du	IMG_PATH, 0
	
startupMsg  	du  "Starting up ", IMG_NAME, "...", 13, 10, \
					"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-*", 13, 10, 0
loadingImgMsg	du	"[ ** ] Loading ", IMG_PATH, "...", 13, 10, 0
imgIsLoadedMsg	du	"[ ** ] Loaded the kernel image at ", IMG_BASE_QUOTED, ".", 13, 10, 0
relocTablesMsg	du	"[ ** ] Relocating system data tables...", 13, 10, 0

;; Error messages
errorMsg		du	"[ !! ] An error occured.", 13, 10, 0
imgNotFoundMsg	du	"[ !! ] The kernel image is not present.", 13, 10, 0
imgLoadErrorMsg du	"[ !! ] Failed to load the kernel image.", 13, 10, 0
	
;; UUID table
EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID:		_EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
EFI_LOADED_IMAGE_PROTOCOL_GUID:			_EFI_LOADED_IMAGE_PROTOCOL_GUID
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID:	_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID

EFI_RSDP_GUID:		_EFI_ACPI_TABLE_GUID	
	
	
section 	'.bss'		data readable writeable discardable

imgHandle		PTR
sysTable		PTR
return			PTR
	
;; Protocol table
EfiFile			PTR
EfiFileSystem	PTR
EfiLoadedImg	PTR
EfiVideoOut		PTR

imgFileHandle	PTR
imgSz			I64	IMG_SIZE

videoInfoSz		IN
videoInfo		PTR

acpiTablesSz	I64	; Is used to map ACPI tables from 0x00000000
	
;; Memory map info
memMapKey		IN
memMapDescSz	IN
memMapDescVer	I32
	
section		'.mmap'		data readable discardable	
memMap		rq		1
	
section		'.reloc'	fixups data discardable

