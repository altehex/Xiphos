#ifndef _XSTDVGA_IO_H_
#define _XSTDVGA_IO_H_


#include "attrs.h"
#include <define.h>

#include <include/asm.h>
#include <include/attrs.h>
#include <include/types.h>


/*
 *  The following four functions are for better compilation
 */

static inline void
xstdvga_select_reg(U16 port, U8 index)
{
	register U8  byte __asm__ ("al");
	register U16 __port __asm__ ("dx") = port;

	__asm__ __volatile__
	(
	    "mov     %[index], %%al;"
		"out     %%al, %%dx;"
		"inc     %%dx;"
    : "=r"(byte)
	: "r"(__port), "r"(byte), [index]"g"(index));
}

/* Use these three right after xstdvga_select_<module>_reg */
static inline __PURE__ U8
xstdvga_in_from_reg()
{
	register U8 byte __asm__ ("al");
	
	__asm__ __volatile__
	(
	    "in     %%dx, %%al"
	: "=r"(byte)
	:
	: "dx");

	return byte;
}

static inline void
xstdvga_out_to_reg_with_port_arg(U16 port, U8 byte)
{
	register U8  __byte __asm__ ("al") = byte;
	register U16 __port __asm__ ("dx") = port;
	
	__asm__ __volatile__
	(
	    "out    %%al, %%dx"
    :
	: "r"(__byte), "r"(__port));
}

static inline void
xstdvga_out_to_reg_without_port_arg(U8 byte)
{
	register U8  __byte __asm__ ("al") = byte;
	
	__asm__ __volatile__
	(
	    "out    %%al, %%dx"
    :
	: "r"(__byte)
	: "dx");
}

#define xstdvga_out_to_reg(_1, ...) _Generic((_1), \
											 U8:  xstdvga_out_to_reg_without_port_arg, \
											 U16: xstdvga_out_to_reg_with_port_arg) (_1, ##__VA_ARGS__)

static inline void
xstdvga_select_crt_reg(U8 index)
{
	xstdvga_select_reg(VGA_CRT_CONTROLLER_COLOR_ADDRESS, index);
}

static inline void
xstdvga_select_graphics_reg(U8 index)
{
	xstdvga_select_reg(VGA_GRAPHICS_CONTROLLER_ADDRESS, index);
}

static inline void
xstdvga_select_sequencer_reg(U8 index)
{
	xstdvga_select_reg(VGA_SEQUENCER_ADDRESS, index);
}


/*
 *  External registers I/O
 */

/* Miscellaneous Output register */
static inline __PURE__ U8
xstdvga_in_from_misc_out_reg()
{
	return in(BYTE, VGA_MISC_OUT_READ);
}

static inline void
xstdvga_out_to_misc_out_reg(U8 data)
{
	out(VGA_MISC_OUT_WRITE, data);
}

/* Status registers */
static inline __PURE__ U8
xstdvga_in_from_in_status_0()
{
	return in(BYTE, VGA_INPUT_STATUS_0);
}

static inline __PURE__ U8
xstdvga_in_from_in_status_1()
{
	return in(BYTE, VGA_INPUT_STATUS_1_COLOR);
}


#endif /* ! _XSTDVGA_IO_H_ */
