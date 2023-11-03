#ifndef _XSTDVGA_CRT_H_
#define _XSTDVGA_CRT_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


static inline void
xstdvga_set_max_scanline(U8 maxScanline)
{
	xstdvga_out_to_crt_reg(VGA_MAX_SCANLINE_INDEX, maxScanline);
}

static __CONST__ U8
__calculate_overflow(U8 oldOverflow, U16 VRS, U16 VDE, U16 VT, U16 LC, U16 SVB)
{
	return (VRS == SAME ?
			    oldOverflow & ((1 << 7) | (1 << 2))
		        :
			    ((VRS & 0x100) >> 6) | ((VRS & 0x200) >> 1)) |
		   (VDE == SAME ?
			    oldOverflow & ((1 << 6) | (1 << 1))
		        :
	     	    ((VDE & 0x100) >> 7) | ((VDE & 0x200) >> 2)) |
		   (VT  == SAME ?
			    oldOverflow & ((1 << 5) | (1 << 0))
		        :
			    ((VT & 0x100) >> 8) | ((VT & 0x200) >> 3))   |
		   (LC  == SAME ?
			    oldOverflow & (1 << 4)
		        :
		        (LC & 0x100) >> 4)                           |
		   (SVB == SAME ?
			    oldOverflow & (1 << 3)
		        :
		        (SVB & 0x100) >> 5);
}

static inline void
xstdvga_set_overflow(U16 VRS, U16 VDE, U16 VT, U16 LC, U16 SVB)
{
	U8 overflow = xstdvga_in_from_crt_reg(VGA_OVERFLOW_INDEX);
	xstdvga_out_to_crt_reg(VGA_OVERFLOW_INDEX,
						   __calculate_overflow(overflow, VRS, VDE, VT, LC, SVB));
}    

static inline void
xstdvga_set_v_display_end(U8 scanlineNumLow8)
{
	xstdvga_out_to_crt_reg(VGA_V_DISPLAY_END_INDEX, scanlineNumLow8);
}

static inline void
xstdvga_set_v_display(U16 scanlineNum)
{
	xstdvga_set_v_display_end((U8)scanlineNum);
	xstdvga_set_overflow(SAME, scanlineNum, SAME, SAME, SAME);
}


#endif /* ! _XSTDVGA_CRT_H_ */
