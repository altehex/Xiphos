	format	PE64 DLL EFI
	stack	STACK_SIZE
	entry	__entry

include "../include/acpi.inc"
include "../include/size.inc"
include "../include/types.inc"
include "../include/boot/uefi.inc"
	
section		'.text'		code executable readable
	
	use64
__entry:
	EFI_INIT	imgHandle, sysTable
	jc		error

;; Get the loaded image interface
	__eficall	EfiBootServices, hdl_protocol,					\
				[imgHandle], EFI_LOADED_IMAGE_PROTOCOL_GUID,	\
				EfiLoadedImg
	
;; Get the file interface
	mov		RCX, [EfiLoadedImg]
	__eficall	EfiBootServices, hdl_protocol,			\
				[RCX + _EfiLoadedImg.devHdl],			\
				EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,	\
				EfiFileSystem

	__eficall	EfiFileSystem, open_vol,	\
				EfiFileSystem, EfiFile
	
;; Load the kernel to RAM
load_kernel:
	__eficall	EfiFile, open,			\
				EfiFile, imgFileHandle,	\
				imgPath, EFI_FILE_MODE_READ, 0	
	test	EAX, EAX
	jz		@f			

	cmp		EAX, EFI_NOT_FOUND
	jne		.error
	__eficall	EfiTextOut, output_string,	\
				EfiTextOut, imgNotFoundMsg
	jmp		$

@@:
_sub_EfiFile	equ imgFileHandle

	mov		RBX, [_sub_EfiFile]
	mov		RCX, RBX
	mov		RBX, [RBX + _EfiFile.read]
	mov		RDX, imgSz
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

;; Set up cores
include "./smp.asm"
	
;; How addresses are passed:
;;------------------------------------*

;; [memMapBase = SYS_TABLES_BASE (0x00000000)] 
;;	mem_map.asm ----+
;;					|
;;					V [gdtBase = (memMap[0].sz + 8) & 0xFFF8 ]
;;				reloc_gdt.asm ----+
;; 								  |
;;								  V [idtBase = (gdtBase + GDT.sz + 8) & 0xFFF8]
;;				 		       int.asm ---+
;; 										  |
;;							              V [pml4Base = (idtBase + IDT_SZ + 0x1000) & 0x...F000]
;; 	                	              paging.asm
	
;; Get memory map
include "./mem_map.asm"

;; Relocate GDT (UEFI has already set it up)
include "./reloc_gdt.asm"
	
;; Set up interrupts
include "./int.asm"
	
;; Set up paging
include "./paging.asm"

;; Get XSDP
include "./setup_args.asm"
	
;; Exit EFI
	xor		R9, R9
	__eficall	EfiBootServices, get_memmap,	\
				memMapSz, [memMap], memMapKey, 	\
				R9, NULL
	
	__eficall	EfiBootServices, exit_bs,	\
				[imgHandle], [memMapKey]
	
	test	EAX, EAX
	jnz 	error
	
	mov		byte [bspReady], 1

CR4_OSFXSR		equ	0000000001000000000b
CR4_OSXMMEXCPT	equ	0000000010000000000b
CR4_OSXSAVE		equ 1000000000000000000b
	
core_init:
;; Wait until BSP finishes
	pause
	bt		qword [bspReady], 0
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
	
;; Load page directory address
	mov		RAX, [pml4Base]
	mov		CR3, RAX
	
;; Set up stack
	mov		RSP, IMG_BASE + IMG_SIZE + 0x2000
	and		SP, 0xF000
	mov		RBP, RSP

;; Setup kinit arguments (sysv amd64 abi)
	mov     RDI, RBP
	mov	    RSI, [corenum]
	
;; Push kernel code
	mov		RAX, IMG_BASE
	push	RAX
	ret

	
;; Default error handler
error:			
	__eficall 	EfiTextOut, output_string, 	\ 
 				EfiTextOut, errorMsg
	xor		RAX, RAX	; EFI_SUCCESS
	ret

	
section		'.data'	data readable
	
;; String table
;;-------------------------------------------
imgPath			du	IMG_PATH, 0

;; Error messages
errorMsg		du	"!!! An error occured.", 13, 10, 0
imgNotFoundMsg	du	"!!! The kernel image is not present.", 13, 10, 0
imgLoadErrorMsg du	"!!! Failed to load the kernel image.", 13, 10, 0
	
;; UUID table
EFI_LOADED_IMAGE_PROTOCOL_GUID:			_EFI_LOADED_IMAGE_PROTOCOL_GUID
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID:	_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID
EFI_MP_SERVICES_PROTOCOL_GUID:			_EFI_MP_SERVICES_PROTOCOL_GUID 
	
EFI_RSDP_GUID:		_EFI_ACPI_TABLE_GUID	

xsdp            PTR
	
imgHandle		PTR
sysTable		PTR
return			PTR
	
EfiFile			PTR
EfiFileSystem	PTR
EfiLoadedImg	PTR

imgFileHandle	PTR
imgSz			I64		IMG_SIZE
	
EfiMP			PTR
_event			PTR
_arg			IN	0
corenum	    	IN
activeCoreNum	IN
procNum			IN
procInfo		EfiProcInfo
	align	4
bspReady		I8
	
pml4Base		PTR
idtBase			PTR
gdtBase			PTR

memMapBase		PTR
	
memMapSz		IN	
memMapKey		IN
memMapDescSz	IN	
memMapDescVer	I32
memMap			PTR	
	
	
section		'.reloc'	fixups data discardable

