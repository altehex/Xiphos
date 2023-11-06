#ifndef _XSTDVGA_IO_H_
#define _XSTDVGA_IO_H_


#include "attrs.h"
#include <define.h>

#include <include/asm.h>
#include <include/attrs.h>
#include <include/types.h>


/*
 *  CRT registers I/O
 */

static inline void
xstdvga_select_crt_reg(U8 index)
{
	out(VGA_CRT_CONTROLLER_COLOR_ADDRESS, index);
}
	
static inline U8
xstdvga_in_from_crt_reg()
{
	return in(BYTE, VGA_CRT_CONTROLLER_COLOR_DATA);
}

static inline void
xstdvga_out_to_crt_reg(U8 data)
{
	out(VGA_CRT_CONTROLLER_COLOR_DATA, data);
}

/*
 *  Graphics registers I/O
 */

static inline void
xstdvga_select_graphics_reg(U8 index)
{
	out(VGA_GRAPHICS_CONTROLLER_ADDRESS, index);
}
	
static inline U8
xstdvga_in_from_graphics_reg()
{
	return in(BYTE, VGA_GRAPHICS_CONTROLLER_DATA);
}

static inline void
xstdvga_out_to_graphics_reg(U8 data)
{
	out(VGA_GRAPHICS_CONTROLLER_DATA, data);
}

/*
 *  Sequencer registers I/O
 */

static inline void
xstdvga_select_sequencer_reg(U8 index)
{
	out(VGA_SEQUENCER_ADDRESS, index);
}
	
static inline U8
xstdvga_in_from_sequencer_reg()
{
	return in(BYTE, VGA_SEQUENCER_DATA);
}

static inline void
xstdvga_out_to_sequencer_reg(U8 data)
{
	out(VGA_SEQUENCER_DATA, data);
}

/*
 *  External registers I/O
 */

/* Miscellaneous Output register */
static inline U8
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
static inline U8
xstdvga_in_from_in_status_0()
{
	return in(BYTE, VGA_INPUT_STATUS_0);
}

static inline U8
xstdvga_in_from_in_status_1()
{
	return in(BYTE, VGA_INPUT_STATUS_1_COLOR);
}



#endif /* ! _XSTDVGA_IO_H_ */
