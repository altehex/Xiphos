	format	PE64 DLL EFI
	stack	STACK_SIZE
	entry	__entry

include "../include/acpi.inc"
include "../include/size.inc"
include "../include/types.inc"
include "../include/boot/uefi.inc"
	
MEM_MAP_SZ  = 65536
PAGE_TABLES_SZ = 1024 * 8 * 6 + 8
	
section		'.text'		code executable readable
	
	use64
__entry:
	EFI_INIT	imgHandle, sysTable
	jc		__error
	
;; Set up video (the snippet is inlined)
include "./video.asm"

	lea		RDX, [startupMsg]
	__eficall 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, RDX

	mov		RBX, 1920 / (3 * 25) - 1
@@:
	dec		RBX

	lea		RDX, [prettyLine1]
	__eficall 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, RDX
	
	cmp		RBX, 0
	jnz		@b
	
	lea		RDX, [prettyLine2]
	__eficall 	EfiTextOut, output_string, 	\ 
	 			EfiTextOut, RDX
	
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

	cmp		EAX, EFI_NOT_FOUND
	jne		.error
	lea		RDX, [imgNotFoundMsg]
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, RDX
	jmp		$

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

;; Zero out <1 MB memory
	mov		RCX, 0xFFFFF / 8
	xor		RAX, RAX
	xor		RDI, RDI
	rep	stosq
	
;; System tables relocation 
include "./reloc_tables.asm"

;; Set up cores
include "./smp.asm"
	
;; Get memory map
include "./mem_map.asm"

;; Set up paging
include "./paging.asm"
	
;; Exit EFI
 	lea		RCX, [memMapSz]
	lea		R8, [memMapKey]
	xor		R9, R9
	__eficall	EfiBootServices, get_memmap,	\
				RCX, [memMap], R8, R9, NULL
	
	__eficall	EfiBootServices, exit_bs,	\
				[imgHandle], [memMapKey]
	
	test	EAX, EAX
	jnz 	__error
	
	mov		byte [bspReady], 1

CR4_OSFXSR		equ	0000000001000000000b
CR4_OSXMMEXCPT	equ	0000000010000000000b
CR4_OSXSAVE		equ 1000000000000000000b
	
core_init:
;; Wait until BSP finishes
	mov		AL, byte [bspReady]
	pause
	bt		AX, 0
	jnc		core_init

;; Enable SSE
	mov		RAX, CR0
	and		AX, 0xFFFB
	or		AX, 0x2
	mov		CR0, RAX
	mov		RAX, CR4
	or		EAX, CR4_OSFXSR + CR4_OSXMMEXCPT + CR4_OSXSAVE
	mov		CR4, RAX

;; Enable AVX
	xor		RCX, RCX
	xgetbv
	or		EAX, 7
	xsetbv

;; ;; Load page directory address
;; 	mov		RAX, [pml4Base]
;; 	mov		CR3, RAX

;; ;; Set up stack
;; 	mov		RBX, [memMapBase]
;; 	add		RBX, [RBX + 4 + 8]
;; 	jmp		@f

;; .find_free_region:
;; 	sub		RBX, 20

;; @@:
;; 	mov		EAX, dword [RBX - 20]
;; 	cmp		EAX, __RAM
;; 	jne		.find_free_region

;; 	mov		RSP, [RBX - 20 + 4]
;; 	add		RSP, [RBX - 20 + 4 + 8]
	
;; 	mov		RAX, [coreNum]
;; 	shl		RAX, 10
;; 	sub		RSP, RAX
;; 	and		SPL, 0xF0
;; 	mov		RBP, RSP

;; Push kernel code
	mov		RAX, IMG_BASE
	push	RAX
	mov		RAX, [memMapBase]
	
	ret
	
	
;; Default error handler
	use64
__error:			
	__eficall 	EfiTextOut, output_string, 	\ 
 				EfiTextOut, errorMsg
	xor		RAX, RAX	; EFI_SUCCESS
	ret						

	
section		'.rodata'	data readable
	
;; String table
;;-------------------------------------------
imgPath			du	IMG_PATH, 0
	
startupMsg  	du  "Starting up ", IMG_NAME, "...", 13, 10,	\
					"*-+", 0
prettyLine1		du	"--+", 0
prettyLine2		du  "-*", 13, 10, 0
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
EFI_MP_SERVICES_PROTOCOL_GUID:			_EFI_MP_SERVICES_PROTOCOL_GUID 
	
EFI_RSDP_GUID:		_EFI_ACPI_TABLE_GUID	
	
	
section 	'.bss'		data readable writeable discardable
	
imgHandle		PTR
sysTable		PTR
return			PTR
	
EfiFile			PTR
EfiFileSystem	PTR
EfiLoadedImg	PTR

imgFileHandle	PTR
imgSz			I64		IMG_SIZE

EfiVideoOut		PTR
videoInfoSz		IN
videoInfo		PTR
fbBase			PTR

EfiMP			PTR
__event			PTR
coreNum			IN
activeCoreNum	IN
procNum			IN
procInfo		EfiProcInfo
	align	4
bspReady		I8

acpiTablesBase	PTR
acpiTablesSz	I64	; Is used to map ACPI tables region
	
;; Memory map info
memMapBase		PTR
	
memMapSz		IN	
memMapKey		IN
memMapDescSz	IN	
memMapDescVer	I32
memMap			PTR	
	
pml4Base			PTR
	
	
section		'.reloc'	fixups data discardable

