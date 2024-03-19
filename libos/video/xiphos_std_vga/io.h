#ifndef _XSTDVGA_IO_H_
#define _XSTDVGA_IO_H_


#include "attrs.h"
#include <define.h>

#include <include/asm.h>
#include <include/attrs.h>
#include <include/types.h>


/*
 *  The following four functions are for better compilation.
 */

static inline void
xstdvga_select_reg(U16  port,
				   U8   index)
{
	register U8   byte   __asm__ ("al");
	register U16  __port __asm__ ("dx") = port;

	/* NOTE: Removing __volatile__ makes compiler omit this funtion */
	__asm__ __volatile__
	(
	    "mov     %[index], %%al;"
		"out     %%al, %%dx;"
		"inc     %%dx;"
    : "=r"(byte)
	: "r"(__port), "r"(byte), [index]"g"(index));
}

/* Use these three right after xstdvga_select_reg */
static inline __PURE__ U8
xstdvga_in_from_reg(void)
{
	register U8 byte __asm__ ("al");
	
	__asm__
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
	register U8   __byte __asm__ ("al") = byte;
	register U16  __port __asm__ ("dx") = port;
	
	__asm__
	(
	    "out    %%al, %%dx"
    :
	: "r"(__byte), "r"(__port));
}

static inline void
xstdvga_out_to_reg_without_port_arg(U8 byte)
{
	register U8  __byte __asm__ ("al") = byte;
	
	__asm__
	(
	    "out    %%al, %%dx"
    :
	: "r"(__byte)
	: "dx");
}

#define xstdvga_out_to_reg(_1, ...) _Generic((_1), \
											 U8:  xstdvga_out_to_reg_without_port_arg, \
											 U16: xstdvga_out_to_reg_with_port_arg) (_1, ##__VA_ARGS__)

/*
 *  Macros
 */

#define APPLY_MASKS(INDEX, ...) \
	(U8) ((_##INDEX & (INDEX##_MASK1(__VA_ARGS__))) | (INDEX##_MASK2(__VA_ARGS__)))

/*
 *  I/O for CRTC, graphics and sequencer registers
 *  (where you need an index for addressing registers)
 */
#define SET_REG_ADDR_DATA(PORT, INDEX, ...)   \
	xstdvga_select_reg(PORT, INDEX);          \
	U8 _##INDEX = xstdvga_in_from_reg();      \
	xstdvga_out_to_reg(APPLY_MASKS(INDEX, ##__VA_ARGS__))

/*
 *  Register setting for CRT, graphics and sequencer controllers
 *  should be like this:
 *---------------------------------------------------------------*
 *  1. xstdvga_select_reg():
 *  - Move an address port value to DX
 *  - Output a register index to an address port in DX
 *  - Increment DX by 1 so we get a corresponding data port
 *  2. xstdvga_in_from_reg():
 *  - Input from DX to AL (get the current register value)
 *  3. xstdvga_out_to_reg() with APPLY_MASKS:
 *  - Apply <INDEX>_MASK1 on AL to reset the bits we need to change
 *  - Apply <INDEX>_MASK2 on AL to change the needed bits
 *  - Output to DX
 *
 *  Setting registers of one controller in bulk reqiores a different
 *  approach.
 */


#endif /* ! _XSTDVGA_IO_H_ */
