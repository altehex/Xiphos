include "./types.inc"

;; Macros
;;-------------------------------------

include "./types.inc"


EFI_SYSTEM_TABLE_SIGNATURE	equ 0x20494249


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
macro EFI_CALL interface,	\
	  		   func, 		\
 			   arg1, [arg]
{
	aNum = 0
	
	forward
	rept 10 n:2
	\{
 		if ~ arg eq
 		   aNum = aNum + 1
 		   if ~ arg eq _REG\#n
 		   	  mov	_REG\#n, arg
 		   end if
 		end if
	\}

	if ~ arg1 eq
		argNum = aNum + 1
		if ~ arg1 eq _REG1
	   		if ~ arg1 in <_INTERFACES>
	   			mov		_REG1, arg1
	   		end if
		end if
	end if

	xor		RAX, RAX
	mov		AL, aNum

	if interface in	<_INTERFACES>
	 	mov		RBX, [sysTable]
		mov		RBX, [RBX + EfiSystemTable.#interface]
	else
		if ~ interface eq RBX
			mov		RBX, interface
		end if
	end if

	if arg1 in <_INTERFACES>
		mov		RCX, RBX
	end if

	mov		RBX, [RBX + func]
	
	call	__efi_call
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
	mov     [return],    RSP
}

	
;; Equates
;;-------------------------------------
	
EFI_SUCCESS		equ		0
EFI_LOAD_ERROR	equ		1

	
;; Structs
;;--------------------------------------
macro struct name
{
	virtual at 0
		name name
	end virtual
}
	
struc EfiTableHeader {
	.sig			I64
	.rev 			I32
	.hdrSz			I32
	.crc32			I32
	._res			I32
}
	
struc EfiSystemTable {
	.hdr			EfiTableHeader
	.vendor			PTR
	.rev			I32
	.conInHdl		PTR
	.conIn			PTR
	.conOutHdl		PTR
	.conOut			PTR
	.stdErrHdl		PTR
	.stdErr			PTR
	.rts			PTR
	.bs				PTR
	.entryNum		IN
	.conf			PTR
}
struct EfiSystemTable

struc EfiTextInProtocol {
}
struct EfiTextInProtocol

struc EfiTextOutProtocol {
	.reset			PTR
	.output_string	PTR
}
struct EfiTextOutProtocol
	
	
section		".text" code executable readable

__efi_call:
	mov		[return], RSP
	and		ESP, 0xFFFFFFF0

	bt		EAX, 0
	jnc		@f
	push	RAX

	rept 7 n:5
	{
		reverse
@@:
		cmp		AL, n
		jb		@f
		push	_REG#n
	}
@@:
	sub		RSP, 4 * 8
	call	RBX
	
	mov		RSP, [return]
	ret


section 	'.data' data readable writeable
	
imgHandle		rq 	1
sysTable		rq 	1
return			rq  1
	
section '.reloc' fixups data discardable
