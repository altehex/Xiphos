if ~ defined _UEFI_INC_
define _UEFI_INC_
	
;; Macros
;;-------------------------------------

include "./types.inc"


define _INTERFACES 	conInHdl,			\
					EfiTextIn,			\
					conOutHdl,			\
					EfiTextOut,			\
					stdErrHdl,			\
					stdErr,				\
					EfiRuntimeServices,	\
					EfiBootServices


	
macro EFI_CALL interface*,	\
				func*, 		\
 				a1, a2, a3, a4, [a]
{
	_aNum = _aNum_#func

	if _aNum > 0

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
			mov		RBX, interface
		end if
	end if

	if a1 in <_INTERFACES>
		mov		RCX, RBX
	else
		mov		RCX, a1
	end if

	mov		RBX, [RBX + _#interface#.#func]

	if _aNum > 4
		push	RAX
		mov		[return], RSP
		and		ESP, 0xFFFFFFF0

;; Not sure yet, how this part is going to work
		n = 11
		reverse
		if n <= _aNum & n >= 5
			mov		RAX, a
			push	RAX
			n = n - 1
		end if
	end if
	
	end if		; _aNum > 0
	
	call	RBX
	
	if _aNum > 4
		mov		RSP, [return]
		pop		RAX
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

__sysTable equ _sysTable
}

	
;; Equates
;;-------------------------------------*
	
EFI_SUCCESS				equ		0
EFI_LOAD_ERROR			equ		1
EFI_INVALID_PARAMETER	equ		2

EFI_NOT_FOUND			equ		14

EFI_SYSTEM_TABLE_SIGNATURE	equ 0x20494249

	
;; Structs
;;--------------------------------------*
macro struct name
{
	virtual at 0
		name name
	end virtual
}
	
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
struct EfiSystemTable

_aNum_exit				equ 4
_aNum_get_memmap		equ 5
_aNum_locate_protocol	equ	3
	
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
	.img_load				PTR
	.img_start				PTR
	.exit					PTR
	.img_unload				PTR
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
struct _EfiBootServices
	
struc _EfiTextIn {
}
struct _EfiTextIn

_aNum_clear_scr			equ 1
_aNum_output_string		equ 2
	
struc _EfiTextOut {
	.reset				PTR
	.output_string		PTR
	.test_string		PTR
	.query_mode			PTR
	.set_mode			PTR
	.set_attr			PTR
	.clear_scr			PTR
}
struct _EfiTextOut


section		'.data'		data readable writeable
;; UUIDs
EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID:
	dd	0x9042A9DE
	dw	0x23DC, 0x4A38
	db  0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A


	
;; More equates
;;---------------------------------*

NULL	equ	0x00
	
;; Color attributes
EFI_LIGHTGRAY			equ 0x07

EFI_BACKGROUD_BLACK		equ	0x00

end if	; ~_UEFI_INC_
