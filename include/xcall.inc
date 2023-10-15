
STACK_ALIGN = 8
	
;; Default (or not yet. have to include it in the toolchain) calling convention
;; ----(Info)-----------------*
;; Return values          - RAX, RBX
;; Parameter registers    - RCX, RDX, RSI, RDI
;; Caller-saved registers - RAX, RBX, RCX, RDX, RDI, RSI
;; Callee-saved registers - the rest of the registers
;; Some arguments are placed in a stack from right to left
macro	__xcall		func*, a1, a2, a3, a4, [args]
{
	if ~ a1 eq
		if ~ a1 eq RCX
			mov		RCX, a1
		end if
	
		if ~ a2 eq
			if ~ a2 eq RDX
				mov		RDX, a2
			end if

			if ~ a3 eq
				if ~ a3 eq RSI
					mov		RSI, a3
				end if

				if ~ a4 eq
					if ~ a4 eq RDI
						mov		RDI, a4
					end if 	; ~ a4 eq RDI
				end if	; ~ a4 eq
			end if	; ~ a3 eq
		end if	; ~ a2 eq
	end if	; ~ a1 eq

	aNum = 0
	
	common
	if ~ args eq
		push	RBP
		mov		RBP, RSP
		reverse
		push 	args
		aNum = aNum + 1
	end if
	
	call 	func

	if ~ args eq
	   lea		RSP, [RSP + aNum * STACK_ALIGN]
	   pop		RBP
	end if
}

;; __xcall variation with more volatile registers
;; ----(Info)-----------------*
;; Return values          - RAX, RBX
;; Parameter registers    - RCX, RDX, RSI, RDI, R8, R9
;; Caller-saved registers - RAX, RBX, RCX, RDX, RDI, RSI, R8, R9, R10, R11
;; Callee-saved registers - the rest of the registers
;; Arguments are placed in a stack from right to left
macro	__xcall_fast	func, [args]
{
	;; WIP
}
