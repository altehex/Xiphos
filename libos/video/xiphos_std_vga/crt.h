#ifndef _XSTDVGA_CRT_H_
#define _XSTDVGA_CRT_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


/* Registers */
#define CRT_CTRL_COLOR_ADDRESS (U16) 0x3D4
#define CRT_CTRL_COLOR_DATA    (U16) 0x3D5 /* Not used yet */


enum CrtIndex {
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
	VERTICAL_DISPLAY_END,
	OFFSET,
	UNDERLINE_LOCATION,
	START_VERTICAL_BLANKING,
	END_VERTICAL_BLANKING,
	CRTC_MODE_CONTROL,
	LINE_COMPARE
};


#define SET_CRT_REG_FUNCTION(INDEX, ...) \
	SET_REG_ADDR_DATA(CRT_CTRL_COLOR_ADDRESS, INDEX, ##__VA_ARGS__)


/* 
 *  Changes value of Max Scanline register of the CRT controller.
 *--------------------------------------------------------------------*
 */ 
static inline void
xstdvga_set_max_scanline(U8 maxScanline)
{
	xstdvga_select_reg(CRT_CTRL_COLOR_ADDRESS, MAXIMUM_SCAN_LINE);
	xstdvga_out_to_reg(maxScanline);
}

#define OVERFLOW_MASK1(VRS, VDE, VT, LC, SVB) \
	(VRS == SAME ? BIT7 | BIT2 : 0) |         \
    (VDE == SAME ? BIT6 | BIT1 : 0) |         \
	(VT  == SAME ? BIT5 | BIT0 : 0) |         \
	(LC  == SAME ? BIT4        : 0) |         \
	(SVB == SAME ? BIT3        : 0)

#define OVERFLOW_MASK2(VRS, VDE, VT, LC, SVB)                       \
	(VRS != SAME ? ((VRS & BIT9) >> 2) | ((VRS & BIT8) >> 6) : 0) | \
	(VDE != SAME ? ((VDE & BIT9) >> 3) | ((VDE & BIT8) >> 7) : 0) | \
	(VT  != SAME ? ((VT  & BIT9) >> 4) | ((VT  & BIT8) >> 8) : 0) | \
	(LC  != SAME ? ((LC  & BIT8) >> 4)                       : 0) | \
	(SVB != SAME ? ((SVB & BIT8) >> 5)                       : 0)

/*
 *  Changes the value of Overflow register of the CRT controller.
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
	SET_CRT_REG_FUNCTION(OVERFLOW, vrs, vde, vt, lc, svb);
}    

/*
 *  Changes the value of Vertical Display End register of the CRT controller.
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_v_display_end(U8 scanlineNumLow8)
{
	xstdvga_select_reg(CRT_CTRL_COLOR_ADDRESS, VERTICAL_DISPLAY_END);
	xstdvga_out_to_reg(scanlineNumLow8);
}


#define VERTICAL_RETRACE_END_MASK1(P, BW, VRE)      \
	(P   == SAME ? BIT7                      : 0) | \
	(BW  == SAME ? BIT6                      : 0) | \
	(VRE == SAME ? BIT3 | BIT2 | BIT1 | BIT0 : 0)

#define VERTICAL_RETRACE_END_MASK2(P, BW, VRE)              \
	(P   != SAME ? P << 7                            : 0) | \
	(BW  != SAME ? BW << 6                           : 0) | \
	(VRE != SAME ? VRE & (BIT3 | BIT2 | BIT1 | BIT0) : 0)

/*
 *  Changes the value of Vertical Retrace End register of the CRT controller.
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_vertical_retrace_end(const U8 protect,
							     const U8 bandwidth,
							     const U8 vRetraceEnd)
{
	SET_CRT_REG_FUNCTION(VERTICAL_RETRACE_END, protect, bandwidth, vRetraceEnd);
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
