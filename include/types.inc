struc I8
	  { . db ? }

struc I16 {
	align 2
	. dw ?
}

struc I32 {
	align 4
	. dd ?
}

struc I64 {
	align 8
	. dq ?
}

IN		fix I64
PTR		fix	I64
