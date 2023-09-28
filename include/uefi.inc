include "./types.inc"

;; Macros
;;-------------------------------------

include "./types.inc"


_REG1	equ	RCX
_REG2	equ	RDX
_REG3	equ	R8
_REG4	equ	R9
_REG5	equ	R10
_REG6	equ	R11
_REG7	equ	R12
_REG8	equ	R13
_REG9	equ	R14
_REG10	equ	RSI
_REG11	equ	RDI

define _INTERFACES 	conInHdl,		\
					conIn,			\
					conOutHdl,		\
					conOut,			\
					stdErrHdl,		\
					stdErr,			\
					rts, bs

;; func should have the format:
;; <struct>.<service>
;;
;;-(Example)-----------------
;; EFI_CALL conOut, EfiTextOutProtocol.output_string
;;
;; Conditionals with _aNum are a workaround, so fasm
;; won't generate unnecessary moveabs and push instructions
;; (that's the caveat when iterating through group args
;; with rept). This is stupid, but code generates better that way
macro EFI_CALL interface*,	\
	  		   func*, 		\
 			   _aNum*, a1, [a]
{
	if _aNum >= 2
		forward
		rept 10 n:2
		\{
 			if n <= _aNum
 			if ~ a eq _REG\#n
 				mov	_REG\#n, a
 			end if
 			end if
		\}
	end if

	if interface in	<_INTERFACES>
	 	mov		RBX, [sysTable]
		mov		RBX, [RBX + EfiSystemTable.#interface]
	else
		if ~ interface eq RBX
			mov		RBX, interface
		end if
	end if

	if a1 in <_INTERFACES>
		mov		_REG1, RBX
	else
		mov		_REG1, RCX
	end if

	mov		RBX, [RBX + func]

	if _aNum > 4
		stackArgs = _aNum - 4
		mov		[return], RSP
		and		ESP, 0xFFFFFFF0

		rept 7 n:5
		\{
			\reverse

			if n <= stackArgs
				push	_REG\#n
			end if
		\}
	end if
	
	call	RBX
	
	if _aNum > 4
		mov		RSP, [return]
	end if
}
	
macro EFI_INIT
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
	mov		[imgHandle], RCX
	mov		[sysTable],  RDX
}

	
;; Equates
;;-------------------------------------*
	
EFI_SUCCESS				equ		0
EFI_LOAD_ERROR			equ		1
EFI_INVALID_PARAMETER	equ		2

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
	.conIn					PTR
	.conOutHdl				PTR
	.conOut					PTR
	.stdErrHdl				PTR
	.stdErr					PTR
	.rts					PTR
	.bs						PTR
	.entryNum				IN
	.conf					PTR
}
struct EfiSystemTable

struc EfiBootServices {
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
struct EfiBootServices
	
struc EfiTextIn {
}
struct EfiTextIn

struc EfiTextOut {
	.reset				PTR
	.output_string		PTR
	.test_string		PTR
	.query_mode			PTR
	.set_mode			PTR
	.set_attr			PTR
	.clear_scr			PTR
}
struct EfiTextOut


section 	'.data' data readable writeable
	
imgHandle		rq 	1
sysTable		rq 	1
return			rq  1

;; UUIDs
EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID:
	dd	0x9042A9DE
	dw	0x23DC, 0x4A38
	db  0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A

	
section '.reloc' fixups data discardable

	
;; More equates
;;---------------------------------*

NULL	equ	0x00
	
;; Color attributes
EFI_LIGHTGRAY			equ 0x07

EFI_BACKGROUD_BLACK		equ	0x00
