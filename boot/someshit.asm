;; ......
	
PML4_SZ		equ 8
PDP_SZ		equ 1024 * 8
PD_SZ		equ 1024 * 8
PT_SZ		equ	1024 * 8

PDP_U_OFFSET	equ	PAGE_SZ
PDP_K_OFFSET	equ PDP_U_OFFSET + PDP_SZ
PD_U_OFFSET		equ PDP_K_OFFSET + PDP_SZ
PD_K_OFFSET		equ	PD_U_OFFSET + PD_SZ
PT_U_OFFSET		equ	PD_K_OFFSET + PD_SZ
PT_K_OFFSET		equ PT_U_OFFSET + PT_SZ
	
;; Pages for free RAM
;;-------------------------------------*

USER_PAGE_FLAGS		equ 10000111b
	
;; User PML4
	mov		RDI, [pml4Base]
	mov		RAX, RDI
	and		AX, 0xF000
	add		RAX, PDP_U_OFFSET + USER_PAGE_FLAGS
	mov		[RDI], RAX
	
;; User PDP
	mov		RDI, RAX
	xor		RDI, USER_PAGE_FLAGS
 
;; User PD
	add		RDI, PD_U_OFFSET - PDP_U_OFFSET

;; User PT
	add		RDI, PT_U_OFFSET - PD_U_OFFSET
	
;; Pages for the kernel 
;;----------------------a---------------*

KERNEL_PAGE_FLAGS	equ 10000011b
	
;; Kernel PML4
	mov		RDI, [pml4Base]
	mov		RAX, RDI
	
	and		AX, 0xF000
	add		RAX, PDP_K_OFFSET + KERNEL_PAGE_FLAGS
	add		RDI, PML4_SZ
	mov		[RDI], RAX

;; Kernel PDP
	mov		RDI, RAX
	xor		RDI, KERNEL_PAGE_FLAGS
	add		RAX, PD_K_OFFSET - PDP_K_OFFSET
	mov		[RDI], RAX


;; Кол-во записей в PDPE должно(по крайней мере на момент запуска) зависить от кол-ва
;; свободной памяти (сначала нужно определить кол-во страниц для ядра и пользовательской
;; памяти. Например, под 1 ГБ - по одной записи в двух PDPE)
	;; mov		RCX, []
	
	;; jmp		$

;; Kernel PD
	mov		RDI, RAX
	xor		RDI, 11b
	
	add		RDI, PT_K_OFFSET - PD_K_OFFSET

;; Kernel PT
	add		RDI, PT_K_OFFSET - PD_K_OFFSET

	add		RDI, PT_SZ
	mov		[memMapBase], RDI
	
;; ......
