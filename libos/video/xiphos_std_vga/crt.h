#ifndef _XSTDVGA_CRT_H_
#define _XSTDVGA_CRT_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


/* Registers */
/* #define VGA_CRT_CONTROLLER_COLOR_ADDRESS (U16) 0x3D4 */
/* #define VGA_CRT_CONTROLLER_COLOR_DATA    (U16) 0x3D5 */

enum Index {
	HORIZONTAL_TOTAL,
	END_HORIZONTAL_DISPLAY,
	START_HORIZONTAL_BLANKING,
	END_HORIZONTAL_BLANKING,
	START_HORIZONTAL_RETRACE,
	END_HORIZONTAL_RETRACE,
	VERTICAL_TOTAL,
	OVERFLOW,
	PRESET_ROW_SCAN,
	MAXIMUM_SCAN_LINE,
	CURSOR_START,
	CURSOR_END,
	START_ADDRESS_HIGH,
	START_ADDRESS_LOW,
	CURSOR_LOCATION_HIGH,
	CURSOR_LOCATION_LOW,
	VERTICAL_RETRACE_START,
	VERTICAL_RETRACE_END,
	OFFSET,
	UNDERLINE_LOCATION,
	START_VERTICAL_BLANKING,
	END_VERTICAL_BLANKING,
	CRTC_MODE_CONTROL,
	LINE_COMPARE
};


/* Skeleton for register setting functions */
#define SET_CRT_REG_FUNCTION(index, calcFunc, ...)                              \
	xstdvga_select_crt_reg(index);                                              \
    U8 __reg_old = xstdvga_in_from_reg();                                       \
    U16 __port; __asm__ __volatile__ ( "mov %%dx, %0" : "=g"(__port) : : "dx"); \
    xstdvga_out_to_reg(__port, calcFunc(__reg_old, ##__VA_ARGS__))              

#define __APPLY_MASKS(INDEX, ...) \
	(U8) ((_##INDEX & (INDEX##_MASK1(__VA_ARGS__))) | (INDEX##_MASK2(__VA_ARGS__)))

#define _SET_CRT_REG_FUNCTION(INDEX, ...) \
	xstdvga_select_crt_reg(INDEX);        \
	U8 _##INDEX = xstdvga_in_from_reg();  \
	xstdvga_out_to_reg(__APPLY_MASKS(INDEX, ##__VA_ARGS__))

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

/*  The code below is way better and doesn't mess up DX.
 *  Should've done it like this in the first place.
 */

#define OVERFLOW_MASK1(VRS, VDE, VT, LC, SVB) \
	(VRS == SAME ? BIT7 | BIT2 : 0) |                \
    (VDE == SAME ? BIT6 | BIT1 : 0) |                \
	(VT  == SAME ? BIT5 | BIT0 : 0) |                \
	(LC  == SAME ? BIT4 : 0) |                \
	(SVB == SAME ? BIT3 : 0)

#define OVERFLOW_MASK2(VRS, VDE, VT, LC, SVB)                         \
	(VRS != SAME ? ((VRS & BIT9) >> 2) | ((VRS & BIT8) >> 6) : 0) | \
	(VDE != SAME ? ((VDE & BIT9) >> 3) | ((VDE & BIT8) >> 7) : 0) | \
	(VT  != SAME ? ((VT  & BIT9) >> 4) | ((VT  & BIT8) >> 8) : 0) | \
	(LC  != SAME ? ((LC  & BIT8) >> 4) : 0) |                        \
	(SVB != SAME ? ((SVB & BIT8) >> 5) : 0)

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
	_SET_CRT_REG_FUNCTION(OVERFLOW, vrs, vde, vt, lc, svb);
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
