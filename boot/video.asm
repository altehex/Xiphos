vRes = 1080
hRes = 1920

;; ......

	lea		RCX, [EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID]
	lea		R8, [EfiVideoOut]
	__eficall	EfiBootServices, locate_protocol,	\
				RCX, NULL, R8

;; Set 1920x1080x32 mode, if it's supported
set_mode:
	mov		RCX, [EfiVideoOut]
	mov		RCX, [RCX + _EfiVideoOut.mode]
	movsxd	RCX, [RCX + EfiVideoOutMode.maxMode]
	dec		RCX

	;; mov		R13, hRes
	
	
.seek:
	mov		R12, RCX

	mov		RDX, RCX
	lea		R8, [videoInfoSz]
	lea		R9, [videoInfo]
	__eficall	EfiVideoOut, query_mode,	\
				EfiVideoOut, RDX, R8, R9
	
	mov		RSI, [videoInfo]
	lodsd
	lodsd
	cmp		EAX, hRes
	jne		@f
	lodsd
	cmp		EAX, vRes
	jne		@f
	lodsd
	test	EAX, EAX 
	jnz		.done

@@:
	mov		RCX, R12
	loop	.seek

	jmp		.clear_screen
	
.done:
	__eficall	EfiVideoOut, set_mode,	\
				EfiVideoOut, R12
	
.clear_screen:	
	
	__eficall	EfiTextOut, clear_scr, EfiTextOut
;; ......