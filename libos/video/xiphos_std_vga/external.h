#ifndef _XSTDVGA_EXTERNAL_H_
#define _XSTDVGA_EXTERNAL_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


static __CONST__ U8
__calculate_misc_out(const U8 miscOut,
					 const U8 vsyncp,
					 const U8 hsyncp,
					 const U8 oePage,
					 const U8 clockSelect,
					 const U8 ramEn,
					 const U8 ioas)
{
	return (vsyncp == SAME ?
			    miscOut & (1 << VGA_VSYNCP)
			    :
			    vsyncp << VGA_VSYNCP)      |
		   (hsyncp == SAME ?
			    miscOut & (1 << VGA_HSYNCP)
			    :
			    hsyncp << VGA_HSYNCP)      |
		   (oePage == SAME ?
			    miscOut & (1 << VGA_OE_PAGE)
			    :
			    oePage << VGA_OE_PAGE)      |
		   (clockSelect == SAME ?
			    miscOut & (1 << VGA_CLOCK_SEL)
			    :
			    clockSelect << VGA_CLOCK_SEL) |
		   (ramEn == SAME ?
			    miscOut & (1 << VGA_RAM_EN)
			    :
			    ramEn << VGA_RAM_EN)       |
		   (ioas == SAME ?
			    miscOut & (1 << VGA_IOAS)
			    :
			    ioas << VGA_IOAS);
}

static inline void
xstdvga_set_misc_out(const U8 vsyncp,
					 const U8 hsyncp,
					 const U8 oePage,
					 const U8 clockSelect,
					 const U8 ramEn,
					 const U8 ioas)
{
	U8 miscOut = xstdvga_in_from_misc_out_reg();
	xstdvga_out_to_misc_out_reg(__calculate_misc_out(miscOut,
													 vsyncp,
													 hsyncp,
													 oePage,
													 clockSelect,
													 ramEn,
													 ioas));
}
	

#endif /* ! _XSTDVGA_EXTERNAL_H_ */
