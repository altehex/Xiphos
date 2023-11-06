#ifndef _XSTDVGA_GRAPHICS_H_
#define _XSTDVGA_GRAPHICS_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


static __CONST__ U8
__calculate_misc_graphics(const U8 miscGraphics,
						  const U8 memMapSel,
						  const U8 chainOE,
						  const U8 alphaDis)
{
	return (memMapSel == SAME ?
			    miscGraphics & (1 << VGA_MEM_MAP_SEL)
			    :
			    memMapSel << VGA_MEM_MAP_SEL) |
		   (chainOE == SAME ?
			    miscGraphics & (1 << VGA_CHAIN_OE)
			    :
			    chainOE << VGA_CHAIN_OE)   |
		   (alphaDis == SAME ?
			    miscGraphics & (1 << VGA_ALPHA_DIS)
			    :
			    alphaDis << VGA_ALPHA_DIS);
}
	
static inline void
xstdvga_set_misc_graphics(const U8 memMapSel,
						  const U8 chainOE,
						  const U8 alphaDis)
{
	xstdvga_select_graphics_reg(VGA_MISC_GRAPHICS_INDEX);
	U8 miscGraphics = xstdvga_in_from_graphics_reg();
	xstdvga_out_to_graphics_reg(__calculate_misc_graphics(miscGraphics,
														  memMapSel,
														  chainOE,
														  alphaDis));
}


#endif /* ! _XSTDVGA_GRAPHICS_H_ */
