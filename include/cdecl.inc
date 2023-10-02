;; Caller-saved registers: RAX, RCX, RDX
macro	__cdecl	func*, [arg]
{
	push	RBP
	mov		RBP, RSP
	
	reverse
	push	arg
	
	common
	call	func

	mov		RSP, RBP
	pop		RBP
}
