;; ......

;; Maliciously stolen from BOOTBOOT
;; Copyright included because this is based on BOOTBOOT's x86_64-efi/bootboot.c

 ;; * x86_64-efi/bootboot.c
 ;; *
 ;; * Copyright (C) 2017 - 2021 bzt (bztsrc@gitlab)
 ;; *
 ;; * Permission is hereby granted, free of charge, to any person
 ;; * obtaining a copy of this software and associated documentation
 ;; * files (the "Software"), to deal in the Software without
 ;; * restriction, including without limitation the rights to use, copy,
 ;; * modify, merge, publish, distribute, sublicense, and/or sell copies
 ;; * of the Software, and to permit persons to whom the Software is
 ;; * furnished to do so, subject to the following conditions:
 ;; *
 ;; * The above copyright notice and this permission notice shall be
 ;; * included in all copies or substantial portions of the Software.
 ;; *
 ;; * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 ;; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 ;; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 ;; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 ;; * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 ;; * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ;; * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 ;; * DEALINGS IN THE SOFTWARE.
	
include "../include/xcall.inc"
	
	xor		RCX, RCX	; AllocateAnyPages
	mov		R8, [coreNum]
	shl		R8, 10 	; multiply by stack size (1024)
	add		R8, PAGE_SZ - 1
	shr		R8, 12	; divide by page size
	add		R8, 37
	mov		[pageNum], R8
	lea		R9, [pages]
	__eficall	EfiBootServices, alloc_pages,	\
				RCX, EFI_LOADER_DATA, R8, R9
	test	EAX, EAX
	jnz		__error
	
	;; Zero out the allocated memory
	mov		RCX, [pageNum]
	shl		RCX, 9
	xor		RAX, RAX
	mov		RDI, [pages]
	rep	stosq

	mov		RDX, [pages]
	
	mov		RAX, RDX
	xor		RBX, RBX
	mov		BL, DL
	add		RBX, PAGE_SZ + 3
	mov		[RAX], RBX
	
	add		RAX, 511 * 8
	add		RBX, 20
	mov		[RAX], RBX
	
	xor		RBX, RBX
	mov		BL, DL
	add		RBX, 3 + PAGE_SZ * 3
	mov		RCX, 16
	jmp		@f
.pdpe:
	add		RAX, 8
	add		RBX, PAGE_SZ

@@:
	mov		[RAX], RBX
	loop	.pdpe

;; Map 2 MB
	mov		RAX, RDX
	add		RAX, 512 * 3 * 8
	xor		RBX, RBX
	mov		BL, DL
	add		RBX, PAGE_SZ * 2 + 3
	mov		[RAX], RBX

	mov		RAX, RDX
	add		RAX, 512 * 2 * 8
	xor		RBX, RBX
	mov		BL, DL
	add		RBX, 3
	mov		RCX, 512
	jmp		@f
.map:
	add		RAX, 8
	add		RBX, PAGE_SZ

@@:
	mov		[RAX], RBX
	loop	.map

;; 2M PDE
	mov		RAX, RDX
	add		RAX, 512 * 3 * 8
	mov		RCX, 1
	jmp		@f
.pde2m:
	inc		RCX

@@:
	add		RAX, 8
	mov		RBX, RCX
	shl		RBX, 21
	add		RBX, 0x83
	mov		[RAX], RBX
	cmp		RCX, 512 * 16 - 1
	jl		.pde2m

;; Kernel mapping
;; 4K PDPE
	mov		RAX, RDX
	add		RAX, 8 * (20 * 512 + 511)
	xor		RBX, RBX
	mov		BL, DL
	add		RBX, 22 * PAGE_SZ + 3
	mov		[RAX], RBX

;; 4K PDP
	mov		R8, FRAMEBUFFER
	shr		R8, 12 + 9
	and		R8, 0x1FF

	mov		RAX, RDX
	add		RAX, R8
	add		RAX, 22 * 512

	mov		RBX, fbBase
	add		RBX, 0x83
	
	xor		RCX, RCX
	jmp		@f
.pde4k:
	inc		RCX
	add		RAX, 8

	mov		R9, RCX
	shl		R9, 21
	add		RBX, R9
	
@@:
	mov		[RAX], RBX
	
	cmp		RCX, 63
	jge		@f
	xor		R9, R9
	add		R9, R8
	add		R9, RCX
	cmp		R9, 511
	jl		.pde4k

@@:

;; 4K PT

	mov		RCX, IMG_SIZE
	shr		RCX, 12
	jmp		@f
.pt4k:
	
	
@@:

	jmp		$
;; 	mov		R8, RCX	; preserve counter
;; 	mov		RCX, 
;; 	mov		RDX, 
;; 	__xcall		map_page,	\
;; 				RCX, RDX

;; 	mov		RCX, R8
;; 	loop	.pt4k
	
;; 	jmp		$

	
;; map_page:
;; 	mov		RAX, RCX
;; 	shr		RAX, 9 + 12
;; 	and		RAX, 0x1FF

;; 	mov		RDI, [pages]
;; 	add		RDI, 22 * 512
;; 	add		RDI, RAX

;; 	mov		RAX, [RDI]
;; 	mov		RBX, RAX

;; 	not		
	
	ret
	
;; ......
