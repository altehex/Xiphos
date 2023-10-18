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
	xor		RCX, RCX
	xor		R8, R8
	xor		R9, R9
	__eficall	EfiBootServices, create_event,	\
				RCX, TPL_NOTIFY, R8, R9, 		\
				__event
	
	mov		RBX, [coreNum]
.startup_cores:
	dec		RBX

	lea		R8, [procInfo]
	__eficall	EfiMP, get_proc_info,	\
				EfiMP, RBX, R8
	
	mov		EAX, dword [procInfo + EfiProcInfo.status]
	test	EAX, 01b
	jz		@f

	lea		RDX, [core_init]
	mov		R8, RBX
	mov		R9, [__event]
	__eficall	EfiMP, start_this_ap,	\
				EfiMP, RDX, R8, R9,		\
				0, procNum, NULL
	
@@:
	cmp		RBX, 0
	jne		.startup_cores
	
;; ......
