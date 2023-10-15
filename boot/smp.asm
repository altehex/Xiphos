;; ......
	
	lea		RCX, [EFI_MP_SERVICES_PROTOCOL_GUID]
	xor		RDX, RDX
	lea		R8, [EfiMP]
	__eficall	EfiBootServices, locate_protocol,	\
				RCX, RDX, R8

	lea		RDX, [coreNum]
	lea		R8, [activeCoreNum]
	__eficall	EfiMP, get_core_num,	\
				EfiMP, RDX, R8

	mov		RAX, [coreNum]
	cmp		RAX, PAGE_SZ / 4
	jle		@f
	mov		RAX, PAGE_SZ / 4
	mov		[coreNum], RAX
	
@@:
	
;; ......
