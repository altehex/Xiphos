#ifndef _XSTDVGA_DEFINE_H_
#define _XSTDVGA_DEFINE_H_


#include <include/types.h>


/*
 *  --- Misc ---
 */
#define VGA_MEM_BASE_0  (PTR) 0x000A0000
#define VGA_MEM_BASE_1  (PTR) 0x000B0000
#define VGA_MEM_BASE_2  (PTR) 0x000B8000
#define VGA_TEXT_BASE   (CHARPTR) VGA_MEM_BASE_2

#define VGA_PLANE_SZ    0x00010000


#define VGA_PLANE_0   0
#define VGA_PLANE_1   1
#define VGA_PLANE_2   2
#define VGA_PLANE_3   3


#define SAME      255 /*  Is used to specify whether    
					   *  a bit in a register should be
					   *  changed.
					   */

#define BIT0      0x0001
#define BIT1      0x0002
#define BIT2      0x0004
#define BIT3      0x0008
#define BIT4      0x0010
#define BIT5      0x0020
#define BIT6      0x0040
#define BIT7      0x0080
#define BIT8      0x0100
#define BIT9      0x0200


#endif /* ! _XSTDVGA_DEFINE_H_ */
