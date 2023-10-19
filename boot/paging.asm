;; ......
	
PML4_SZ		equ 8 * 2
PDP_SZ		equ 1024 * 8
PD_SZ		equ 1024 * 8
PT_SZ		equ	1024 * 8

;; Create PML4
	mov		RDI, [pml4Base]
	

;; Create PDP
	add		RDI, PML4_SZ
 
;; Create PD
	add		RDI, PDP_SZ

;; Create PT
	add		RDI, PD_SZ

	add		RDI, PT_SZ
	mov		[memMapBase], RDI
	
;; ......
