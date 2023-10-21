PAGE_FLAGS	equ	10000111b

;; R15: page size
;; R14: total RAM

	mov		RAX, [memMapBase]
	mov		RBX, RAX
	mov		RAX, [RAX + 4 + 8]
	mov		R14, [RBX + RAX - 8]
	add		R14, [RBX + RAX - 8 - 8]
	
	mov		EAX, 0x80000001
	cpuid
	mov		R15, 0x200000
	bt		EDX, 26	; 1 << 26
	jnc		@f
	sal		R15, 9
	
;; PML4
@@:
	mov		RAX, [pml4Base]
	mov		RDI, RAX
	and		AX, 0xF000
	or		AL, PAGE_FLAGS
	
	mov		RCX, R14
	shr		RCX, 30 + 5
	cmp		RCX, 1023
	jle		@f
	mov		RCX, 1023
@@:
	mov		R13, RCX
@@:
	add		RAX, 0x1000
	mov		[RDI], RAX

	add		RDI, 8
	loope	@b

	mov		RAX, [pml4Base]
	mov		RCX, R13

	bt		R15, 30
	jc		pdp_1gb

	

	jmp		done
	
;; PDP (1 GB)
pdp_1gb:
	mov		RDI, [RAX + RCX * 8]
	and		DI, 0xF000

	
	
	loope	pdp_1gb
	
	
	jmp		$

done:	
