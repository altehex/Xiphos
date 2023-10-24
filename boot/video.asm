V_RES = 1080
H_RES = 1920

;; ......

	xor		RDX, RDX
	__eficall	EfiBootServices, locate_protocol,	\
				EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 	\
				RDX, EfiVideoOut

;; Set 1920x1080x32 mode, if it's supported
set_mode:
	mov		RCX, [EfiVideoOut]
	mov		RCX, [RCX + _EfiVideoOut.mode]
	mov		ECX, dword [RCX + EfiVideoOutMode.maxMode]
	dec		ECX
	
.seek:
	mov		R12D, ECX

	mov		RDX, RCX
	__eficall	EfiVideoOut, query_mode,	\
				EfiVideoOut, RDX,			\
				videoInfoSz, videoInfo

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

;; Not sure if i'll need it
;; ;; Get GOP framebuffer
;; 	mov		RAX, [EfiVideoOut]
;; 	mov		RAX, [RAX + _EfiVideoOut.mode]
;; 	mov		RAX, [RAX + EfiVideoOutMode.fbBase]
;; 	mov		[fbBase], RAX
	
;; ......
