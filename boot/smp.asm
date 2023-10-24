;; ......
	
	xor		RDX, RDX
	__eficall	EfiBootServices, locate_protocol,	\
				EFI_MP_SERVICES_PROTOCOL_GUID, RDX, \
				EfiMP

	__eficall	EfiMP, get_core_num,	\
				EfiMP, coreNum, activeCoreNum

	xor		RCX, RCX
	xor		R8, R8
	xor		R9, R9
	__eficall	EfiBootServices, create_event,	\
				RCX, TPL_NOTIFY, R8, R9, 		\
				__event
	
	mov		RBX, [coreNum]
	cmp		RBX, PAGE_SZ / 4
	jle		startup_cores
	mov		RBX, PAGE_SZ / 4
startup_cores:
	dec		RBX

	__eficall	EfiMP, get_proc_info,	\
				EfiMP, RBX, procInfo
	
	bt		[procInfo + EfiProcInfo.status], 0
	jc		@f

	__eficall	EfiMP, start_this_ap,	\
				EfiMP, core_init, RBX, 	\
				[__event], 0, NULL, NULL
	
@@:
	cmp		RBX, 0
	jne		startup_cores
	
;; ......
