macro EFI_CALL protocol,	\
	  		   func, 		\
			   a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11
{
	aNum = 0
	if ~ a11
	    aNum = aNum + 1
	    if ~ a11 eq RDI
	   	    mov RDI, a11
		end if
	end if
}

macro EFI_INIT imgHandle,	\
	  		   sysTable,	\
			   return
{
	clc
	or		RDX, RDX
	jz		.err
	cmp		dword [RDX], 0x20494249
	je		@f
.err:
	XOR		RCX, RCX
	xor		RDX, RDX
	stc
@@:
	mov		[imgHandle], RCX
	mov		[sysTable], RDX
	mov     [return], RSP
}

EFI_SUCCESS		equ		0
EFI_LOAD_ERROR	equ		1

EFI_BOOT_SERVICES		equ		0x60
