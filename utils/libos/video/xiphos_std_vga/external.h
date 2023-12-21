#ifndef _XSTDVGA_EXTERNAL_H_
#define _XSTDVGA_EXTERNAL_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


#define MISC_OUT_READ               (U16) 0x3CC
#define MISC_OUT_WRITE              (U16) 0x3C2

/*
 * Miscellaneous Output Register I/O
 *--------------------------------------------------------------------*/
static inline __PURE__ U8
xstdvga_in_from_misc_out_reg()
{
	register U8 byte __asm__ ("al");
	
	__asm__
	(
	    "mov    %1, %%dx;"
	    "in     %%dx, %%al;" 
		"sub    %2, %%dx"    /* Prepare for write */
	: "=r"(byte)
	: "g"(MISC_OUT_READ), "g"(MISC_OUT_READ - MISC_OUT_WRITE)
	: "dx");

	return byte;
}

#define VSYNCP_BIT  BIT7
#define HSYNCP_BIT  BIT6
#define OEP_BIT     BIT5
#define CS_BIT      BIT3 | BIT2
#define RAMEN_BIT   BIT1
#define IOAS_BIT    BIT0

#define MISC_OUT_MASK1(VSYNCP, HSYNCP, OEP, CS, RAMEN, IOAS) \
	(VSYNCP == SAME ? VSYNCP_BIT : 0 ) | \
	(HSYNCP == SAME ? HSYNCP_BIT : 0 ) | \
	(OEP    == SAME ? OEP_BIT    : 0 ) | \
	(CS     == SAME ? CS_BIT     : 0 ) | \
	(RAMEN  == SAME ? RAMEN_BIT  : 0 ) | \
	(IOAS   == SAME ? IOAS_BIT   : 0 )

#define MISC_OUT_MASK2(VSYNCP, HSYNCP, OEP, CS, RAMEN, IOAS) \
	(VSYNCP != SAME ? VSYNCP << 7 : 0 ) | \
	(HSYNCP != SAME ? HSYNCP << 6 : 0 ) | \
	(OEP    != SAME ? OEP << 5    : 0 ) | \
	(CS     != SAME ? CS << 2     : 0 ) | \
	(RAMEN  != SAME ? RAMEN << 1  : 0 ) | \
	(IOAS   != SAME ? IOAS << 0   : 0 )

#define CLOCK_25MHZ 0
#define CLOCK_28MHZ 1

/* 
 *  Changes value of Miscellaneous Output Register
 *--------------------------------------------------------------------*
 *  vsyncp:      Vertical Sync Polarity
 *  hsyncp:      Horizontal Sync Polarity
 *  oePage:      Odd/Even Page Select
 *  clockSelect: Clock Select (display timing)
 *  ramEn:       RAM Enable
 *  ioas:        Input/Output Address Select
 *  All the args should be 0, 1 or SAME. clockSelect is the exception, as
 *  it can be CLOCK_25MHZ or CLOCK_28MHZ.
 */ 
static inline void
xstdvga_set_misc_out(const U8 vsyncp,
					 const U8 hsyncp,
					 const U8 oePage,
					 const U8 clockSelect,
					 const U8 ramEn,
					 const U8 ioas)
{
	U8 _MISC_OUT = xstdvga_in_from_misc_out_reg();
	xstdvga_out_to_reg(APPLY_MASKS(MISC_OUT, vsyncp, hsyncp,
								   oePage, clockSelect, ramEn, ioas));
}


/*
 *  Status registers I/O
 */

#define VGA_INPUT_STATUS_0              (U16) 0x3C2

static inline __PURE__ U8
xstdvga_in_from_in_status_0()
{
	return in(BYTE, VGA_INPUT_STATUS_0);
}

#define VGA_INPUT_STATUS_1_COLOR        (U16) 0x3DA

static inline __PURE__ U8
xstdvga_in_from_in_status_1()
{
	return in(BYTE, VGA_INPUT_STATUS_1_COLOR);
}


#endif /* ! _XSTDVGA_EXTERNAL_H_ */
