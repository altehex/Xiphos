#ifndef _XSTDVGA_IO_H_
#define _XSTDVGA_IO_H_


#include "attrs.h"
#include <define.h>

#include <include/asm.h>
#include <include/attrs.h>
#include <include/types.h>


static inline U8
xstdvga_in_from_crt_reg(U8 index)
{
	U8 reg;
	out(VGA_CRT_CONTROLLER_COLOR_ADDRESS, index);
	return in(reg, VGA_CRT_CONTROLLER_COLOR_DATA);
	/* return reg = in_byte(VGA_CONTROLLER_DATA) */
}

static inline void
xstdvga_out_to_crt_reg(U8 index, U8 data)
{
	out(VGA_CRT_CONTROLLER_COLOR_ADDRESS, index);
	out(VGA_CRT_CONTROLLER_COLOR_DATA, data);
}


#endif /* ! _XSTDVGA_IO_H_ */
