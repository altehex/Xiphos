if ~ defined _UEFI_INC_
define _UEFI_INC_ 1
	
;; Macros
;;-------------------------------------

include "../types.inc"
include "../macro.inc"
	
	
EfiVirtAddr	fix I64
EfiPhysAddr	fix I64
	

define _INTERFACES 	conInHdl,			\
					EfiTextIn,			\
					conOutHdl,			\
					EfiTextOut,			\
					stdErrHdl,			\
					stdErr,				\
					EfiRuntimeServices,	\
					EfiBootServices


	
macro __eficall interface*,	\
				func*, 		\
 				a1, a2, a3, a4, [a]
{
	if ~ a4 eq
		if ~ a4 eq R9
			mov		R9, a4
		end if
	end if

	if ~ a3 eq
		if ~ a3 eq R8
			mov		R8, a3
		end if
	end if

	if ~ a2 eq
		if ~ a2 eq RDX
			mov		RDX, a2
		end if
	end if

	if interface in	<_INTERFACES>
	 	mov		RBX, [__sysTable]
		mov		RBX, [RBX + EfiSystemTable.#interface]
	else
		if ~ interface eq RBX
			mov		RBX, [interface]
		end if
	end if

	if ~ a1 eq
		if a1 in <_INTERFACES> | a1 eq interface
			mov		RCX, RBX
		else
			mov		RCX, a1
		end if
	end if

	mov		RBX, [RBX + _#interface#.#func]

	if ~ a eq
		mov		[return], RSP
		and		ESP, 0xFFFFFFF0

		reverse
		push	a

		common
	end if
	
	call	RBX
	
	if ~ a eq
		mov		RSP, [return]
	end if
}
	
macro EFI_INIT	_imgHandle,	\
				_sysTable
{
	clc
	or		RDX, RDX
	jz		.err
	cmp		dword [RDX], EFI_SYSTEM_TABLE_SIGNATURE
	je		@f
.err:
	xor		RCX, RCX
	xor		RDX, RDX
	stc
@@:
	mov		[_imgHandle], RCX
	
	mov		[_sysTable],  RDX
__sysTable = _sysTable
}

	
;; Equates
;;-------------------------------------*
	
EFI_SUCCESS				=		0 
EFI_LOAD_ERROR			=		1
EFI_INVALID_PARAMETER	=		2
EFI_UNSUPPORTED			=		3

EFI_BUFFER_TOO_SMALL	=		5
	
EFI_DEVICE_ERROR		= 		7
EFI_WRITE_PROTECTED		=		8
EFI_OUT_OF_RESOURCES	=		9
EFI_VOLUME_CORRUPTED	=		10
EFI_VOLUME_FULL			=		11
EFI_NO_MEDIA			=		12
EFI_MEDIA_CHANGED		=		13
EFI_NOT_FOUND			=		14
EFI_ACCESS_DENIED		=		15
	
EFI_SYSTEM_TABLE_SIGNATURE	= 0x20494249

	
;; Structs
;;--------------------------------------*

;; Interfaces
struc EfiTableHeader {
	.sig					I64
	.rev					I32
	.hdrSz					I32
	.crc32					I32
	._res					I32
}
	
struc EfiSystemTable {
	.hdr					EfiTableHeader
	.vendor					PTR
	.rev					I32
	.conInHdl				PTR
	.EfiTextIn				PTR
	.conOutHdl				PTR
	.EfiTextOut				PTR
	.stdErrHdl				PTR
	.stdErr					PTR
	.EfiRuntimeServices		PTR
	.EfiBootServices		PTR
	.entryNum				IN
	.conf					PTR
}

struc _EfiBootServices {
	.hdr					EfiTableHeader
	.raise_tpl				PTR
	.restore_tpl			PTR
	.alloc_pages			PTR
	.free_pages				PTR
	.get_memmap				PTR
	.alloc_pool				PTR
	.free_pool				PTR
	.create_event			PTR
	.set_timer				PTR
	.wait_for_event			PTR
	.sig_event				PTR
	.close_event			PTR
	.check_event			PTR
	.install_interface		PTR
	.reinstall_interface	PTR
	.uninstall_interface	PTR
	.hdl_protocol			PTR
	._res					PTR
	.reg_protocol_notify	PTR
	.locate_hdl				PTR
	.locate_dev_path		PTR
	.install_conf_table		PTR
	.load_img				PTR
	.start_img				PTR
	.exit					PTR
	.unload_img				PTR
	.exit_bs				PTR
	.get_next_mono_count	PTR
	.stall					PTR
	.set_watchdog_timer		PTR
	.connect_controller		PTR
	.disconnect_controller	PTR
	.open_protocol			PTR
	.close_protocol			PTR
	.open_protocol_info		PTR
	.protocols_per_hdl		PTR
	.locate_hdl_buf			PTR
	.locate_protocol		PTR
	.install_mul_protocols	PTR
	.uninstall_mul_protocols	PTR
	.calculate_crc32		PTR
	.copy_mem				PTR
	.set_mem				PTR
	.create_event_EX		PTR
}
	
struc _EfiTextIn {
}

struc _EfiTextOut {
	.reset				PTR
	.output_string		PTR
	.test_string		PTR
	.query_mode			PTR
	.set_mode			PTR
	.set_attr			PTR
	.clear_scr			PTR
}

struc _EfiFileSystem {
	.rev			I64
	.open_vol		PTR
}

EFI_FILE_MODE_READ	equ		0x0000000000000001
	
struc _EfiFile {
	.rev			I64
	.open			PTR
	.close			PTR
	.delete			PTR
	.read			PTR
}

struc _EfiLoadedImg {
	.rev			I32
	.parentHdl		PTR
	.sysTable		PTR
	.devHdl			PTR
	.filePath		PTR
	._res			PTR
}

struc _EfiLoadFile {
	.load_file		PTR
}

struc _EfiVideoOut {
	.query_mode		PTR
	.set_mode		PTR
	.blt			PTR
	.mode			PTR			; EfiVideoOutMode
}
	
	
;; Data structures
struc EfiConfTable {
	.guid_q0		I64
	.guid_q1		I64
	.table			PTR
}
EfiConfTable_ENTRY_SZ	equ	8 * 3
	
struc EfiMemoryDescriptor {
	.type			I32
	.physStart		EfiPhysAddr
	.virtStart		EfiVirtAddr
	.numOfPages		I64
	.attrs			I64
}

;; Memory attributes
EFI_MEMORY_UC 				equ		0x0000000000000001
EFI_MEMORY_WC 				equ		0x0000000000000002
EFI_MEMORY_WT 				equ		0x0000000000000004
EFI_MEMORY_WB 				equ		0x0000000000000008
EFI_MEMORY_UCE 				equ		0x0000000000000010
EFI_MEMORY_WP 				equ		0x0000000000001000
EFI_MEMORY_RP 				equ		0x0000000000002000
EFI_MEMORY_XP 				equ		0x0000000000004000
EFI_MEMORY_NV 				equ		0x0000000000008000
EFI_MEMORY_MORE_RELIABLE 	equ		0x0000000000010000
EFI_MEMORY_RO 				equ		0x0000000000020000
EFI_MEMORY_SP 				equ		0x0000000000040000
EFI_MEMORY_CPU_CRYPTO 		equ		0x0000000000080000
EFI_MEMORY_RUNTIME 			equ		0x8000000000000000
	
struc EfiVideoOutMode {
	.maxMode		I32
	.mode			I32
	.info			PTR			; EfiVideoOutModeinfo
	.infoSz			IN
	.fbBase			EfiPhysAddr
	.fbSz			IN
}

struc EfiPixelBitmask {
	.redMask		I32
	.greenMask		I32
	.blueMask		I32
	._res			I32
}

struc EfiVideoOutModeInfo {
	.ver			I32
	.hRes			I32
	.vRes			I32
	.pixFmt			I32
	.pixInfo		EfiPixelBitmask
	.pixPerLine		I32
}
	

;; UUIDs
macro _EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
{
	dd	0x9042A9DE
	dw	0x23DC, 0x4A38
	db  0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A
}

macro _EFI_LOADED_IMAGE_PROTOCOL_GUID
{
	dd	0x5B1B31A1
	dw	0x9562, 0x11D2
	db	0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B
}
	
macro _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID
{
	dd	0x964E5B22
	dw	0x6459, 0x11D2
	db  0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B
}

	
macro _EFI_ACPI_TABLE_GUID
{
	dd	0x8868E871
	dw	0xE4F1, 0x11D3
	db	0xBC, 0x22, 0x00, 0x80, 0xC7, 0x3C, 0x88, 0x81
}

macro _EFI_DTB_TABLE_GUID
{
	dd	0xB1B621D5
	dw	0xF19C, 0x41A5
	db	0x83, 0x0B, 0xD9, 0x15, 0x2C, 0x69, 0xAA, 0xE0
}

	
;; More equates
;;---------------------------------*

NULL	=	0x00
	
;; Color attributes
EFI_LIGHTGRAY			= 	0x07

EFI_BACKGROUD_BLACK		=	0x00

;; Revisions
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION	=	0x00010000

;; EFI_GRAPHICS_PIXEL_FORMAT
PixelRedGreenBlueReserved8BitPerColor	equ		0
PixelBlueGreenRedReserved8BitPerColor	equ		1

;; EFI_ALLOCATE_TYPE
EFI_ALLOCATE_ANY_PAGES		equ		0

;; EFI_MEMORY_TYPE
EFI_RESERVED_MEM	=	 0	
EFI_LOADER_CODE		=	 1
EFI_LOADER_DATA		=	 2
EFI_BS_CODE			=	 3
EFI_BS_DATA			=	 4
EFI_RTS_CODE		=	 5
EFI_RTS_DATA		=	 6
EFI_FREE			=	 7
EFI_UNUSABLE		=	 8
EFI_ACPI_RECLAIM	=	 9
EFI_ACPI_NVS		=	10
EFI_IO				=	11
EFI_IO_PORTS		=	12
EFI_PAL_CODE		=	13
EFI_PERSISTENT		=	14
	

TABLE	\
	EfiSystemTable,			\
	_EfiBootServices,		\
	_EfiTextIn,				\
	_EfiTextOut,			\
	_EfiFileSystem,			\
	_EfiFile,				\
	_EfiLoadedImg,			\
	_EfiLoadFile,			\
	_EfiVideoOut,			\
	EfiConfTable,			\
	EfiMemoryDescriptor,	\
	EfiVideoOutMode,		\
	EfiPixelBitmask,		\
	EfiVideoOutModeInfo
	
	
end if	; ~_UEFI_INC_