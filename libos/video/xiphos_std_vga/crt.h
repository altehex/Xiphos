#ifndef _XSTDVGA_CRT_H_
#define _XSTDVGA_CRT_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


/* Skeleton for register setting functions */
#define SET_CRT_REG_FUNCTION(index, calcFunc, ...)                              \
	xstdvga_select_crt_reg(index);                                              \
    U8 __reg_old = xstdvga_in_from_reg();                                       \
    U16 __port; __asm__ __volatile__ ( "mov %%dx, %0" : "=g"(__port) : : "dx"); \
    xstdvga_out_to_reg(__port, calcFunc(__reg_old, ##__VA_ARGS__))              \


/* 
 *  Changes value of Max Scanline register of CRT controller.
 *--------------------------------------------------------------------*
 */ 
static inline void
xstdvga_set_max_scanline(U8 maxScanline)
{
	xstdvga_select_crt_reg(VGA_MAX_SCANLINE_INDEX);
	xstdvga_out_to_reg(maxScanline);
}

/*
 *  Calculates the value of Overflow register based on changed bits
 *  (for xstdvga_set_overflow()).
 *--------------------------------------------------------------------*
 *  overflow: old Overflow register value
 *  The rest of the args should be 0, 1 or SAME.
 */
static __CONST__ U8
__calculate_overflow(U8 overflow, U16 vrs, U16 vde, U16 vt, U16 lc, U16 svb)
{
	return (vrs == SAME ?
			    overflow & ((1 << VGA_VRS9) | (1 << VGA_VRS8))
		        :
			    ((vrs & 0x100) >> 6) | ((vrs & 0x200) >> 1)) |
		   (vde == SAME ?
			    overflow & ((1 << VGA_VDE9) | (1 << VGA_VDE8))
		        :
	     	    ((vde & 0x100) >> 7) | ((vde & 0x200) >> 2)) |
		   (vt  == SAME ?
			    overflow & ((1 << VGA_VT9) | (1 << VGA_VT8))
		        :
			    ((vt & 0x100) >> 8) | ((vt & 0x200) >> 3))   |
		   (lc  == SAME ?
			    overflow & (1 << VGA_LC8)
		        :
		        (lc & 0x100) >> 4)                           |
		   (svb == SAME ?
			    overflow & (1 << VGA_SVB8)
		        :
		        (svb & 0x100) >> 5);
}

/*
 *  Changes the value of Overflow register
 *--------------------------------------------------------------------*
 *  vrs: Vertical Retrace Start  (sets bits 8-9)
 *  vde: Vertical Display End    (sets bits 8-9)
 *  vt:  Vertical Total          (sets bits 8-9)
 *  lc:  Line Compare            (sets bit 8)
 *  svb: Start Vertical Blinking (sets bit 8)
 *  All the args should be 0, 1 or SAME.
 */
static inline void
xstdvga_set_overflow(const U16 vrs,
					 const U16 vde,
					 const U16 vt,
					 const U16 lc,
					 const U16 svb)
{
	SET_CRT_REG_FUNCTION(VGA_OVERFLOW_INDEX, __calculate_overflow,
						 vrs, vde, vt, lc, svb);
}    

/*
 *  Changes the value of Vertical Display End register.
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_v_display_end(U8 scanlineNumLow8)
{
	xstdvga_select_crt_reg(VGA_V_DISPLAY_END_INDEX);
	xstdvga_out_to_reg(scanlineNumLow8);
}

static __CONST__ U8
__calculate_vertical_retrace(const U8 vRetrace,
							 const U8 protect,
							 const U8 bandwidth,
							 const U8 vRetraceEnd)
{
	return (protect == SAME ?
			    vRetrace & (1 << VGA_PROTECT)
			    :
			    protect << VGA_PROTECT)     |
		   (bandwidth == SAME ?
			    vRetrace & (1 << VGA_BANDWIDTH)
			    :
			    bandwidth << VGA_BANDWIDTH) |
		   (vRetraceEnd == SAME ?
			    vRetrace & 0xF
			    :
			    vRetraceEnd);
}
	
static inline void
xstdvga_set_vertical_retrace(const U8 protect,
							 const U8 bandwidth,
							 const U8 vRetraceEnd)
{
	SET_CRT_REG_FUNCTION(VGA_VERTICAL_RETRACE_INDEX, __calculate_vertical_retrace,
						 protect, bandwidth, vRetraceEnd);
}

/*
 *  Sets the Vertical Display End value(in both VDE and Overflow registers). 
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_v_display(const U16 scanlineNum)
{
	xstdvga_set_v_display_end((U8)scanlineNum);
	xstdvga_set_overflow(SAME, scanlineNum, SAME, SAME, SAME);
}


#endif /* ! _XSTDVGA_CRT_H_ */
