V_RES = 1080
H_RES = 1920

;; ......

	lea		RCX, [EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID]
	lea		R8, [EfiVideoOut]
	__eficall	EfiBootServices, locate_protocol,	\
				RCX, NULL, R8

;; Set 1920x1080x32 mode, if it's supported
set_mode:
	mov		RCX, [EfiVideoOut]
	mov		RCX, [RCX + _EfiVideoOut.mode]
	mov		ECX, dword [RCX + EfiVideoOutMode.maxMode]
	dec		ECX
	
.seek:
	mov		R12D, ECX

	lea		R8, [videoInfoSz]
	lea		R9, [videoInfo]
	mov		RDX, RCX
	__eficall	EfiVideoOut, query_mode,	\
				EfiVideoOut, RDX, R8, R9

	mov		RAX, [videoInfo]
	cmp		dword [RAX + EfiVideoOutModeInfo.hRes], H_RES
	jne		@f
	cmp		dword [RAX + EfiVideoOutModeInfo.vRes], V_RES
	jne		@f
	cmp		dword [RAX + EfiVideoOutModeInfo.pixFmt], 1
	je		.done

@@:
	mov		ECX, R12D
	loop	.seek

	jmp		.clear_screen
	
.done:
	__eficall	EfiVideoOut, set_mode,	\
				EfiVideoOut, R12
	
.clear_screen:	
	__eficall	EfiTextOut, clear_scr, EfiTextOut

;; Get GOP framebuffer
	mov		RAX, [EfiVideoOut]
	mov		RAX, [RAX + _EfiVideoOut.mode]
	mov		RAX, [RAX + EfiVideoOutMode.fbBase]
	mov		[fbBase], RAX
	
;; ......
