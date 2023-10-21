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

	cmp		[coreNum], PAGE_SZ / 4
	jle		@f
	mov		[coreNum], PAGE_SZ / 4

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
	
	bt		[procInfo + EfiProcInfo.status], 0
	jc		@f

	lea		RDX, [core_init]
	__eficall	EfiMP, start_this_ap,	\
				EfiMP, RDX, RBX, [__event],		\
				0, procNum, NULL
	
@@:
	cmp		RBX, 0
	jne		.startup_cores
	
;; ......
