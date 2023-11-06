#ifndef _XSTDVGA_CRT_H_
#define _XSTDVGA_CRT_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>

/* 
 *  Changes value of the Max Scanline register of CRT controller.
 *--------------------------------------------------------------------*
 */ 
static inline void
xstdvga_set_max_scanline(U8 maxScanline)
{
	xstdvga_select_crt_reg(VGA_MAX_SCANLINE_INDEX);
	xstdvga_out_to_crt_reg(maxScanline);
}

/*
 *  Calculates the value of Overflow register based on changed bits
 *  (for xstdvga_set_overflow()).
 *--------------------------------------------------------------------*
 *  overflow: old Overflow register value
 *  The rest of the args should be 0, 1 or SAME.
 */
static __CONST__ U8
__calculate_overflow(U8 overflow, U16 VRS, U16 VDE, U16 VT, U16 LC, U16 SVB)
{
	return (VRS == SAME ?
			    overflow & (VGA_VRS9 | VGA_VRS8)
		        :
			    ((VRS & 0x100) >> 6) | ((VRS & 0x200) >> 1)) |
		   (VDE == SAME ?
			    overflow & (VGA_VDE9 | VGA_VDE8)
		        :
	     	    ((VDE & 0x100) >> 7) | ((VDE & 0x200) >> 2)) |
		   (VT  == SAME ?
			    overflow & (VGA_VT9 | VGA_VT8)
		        :
			    ((VT & 0x100) >> 8) | ((VT & 0x200) >> 3))   |
		   (LC  == SAME ?
			    overflow & VGA_LC8
		        :
		        (LC & 0x100) >> 4)                           |
		   (SVB == SAME ?
			    overflow & VGA_SVB8
		        :
		        (SVB & 0x100) >> 5);
}

/*
 *  Changes the value of Overflow register
 *--------------------------------------------------------------------*
 *  VRS: Vertical Retrace Start  (sets bits 8-9)
 *  VDE: Vertical Display End    (sets bits 8-9)
 *  VT:  Vertical Total          (sets bits 8-9)
 *  LC:  Line Compare            (sets bit 8)
 *  SVB: Start Vertical Blinking (sets bit 8)
 *  All the args should be 0, 1 or SAME.
 */
static inline void
xstdvga_set_overflow(U16 VRS, U16 VDE, U16 VT, U16 LC, U16 SVB)
{
	xstdvga_select_crt_reg(VGA_OVERFLOW_INDEX);
	U8 overflow = xstdvga_in_from_crt_reg();
	xstdvga_out_to_crt_reg(__calculate_overflow(overflow, VRS, VDE, VT, LC, SVB));
}    

/*
 *  Changes the value of Vertical Display End register.
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_v_display_end(U8 scanlineNumLow8)
{
	xstdvga_select_crt_reg(VGA_V_DISPLAY_END_INDEX);
	xstdvga_out_to_crt_reg(scanlineNumLow8);
}

/*
 *  Sets the Vertical Display End value(in both VDE and Overflow registers). 
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_v_display(U16 scanlineNum)
{
	xstdvga_set_v_display_end((U8)scanlineNum);
	xstdvga_set_overflow(SAME, scanlineNum, SAME, SAME, SAME);
}


#endif /* ! _XSTDVGA_CRT_H_ */
