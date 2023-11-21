#include <mode.h>

#include <include/types.h>

#include <xiphos_std_vga.h>


void
xstdcon_set_mode_mparm(const U16 height,
					   __UNUSED__ const U16 width,
					   const U8  colorDepth,
					   const U8  textGraphics)
{
    /* Set text/graphics mode */
	xstdvga_set_map_mask(1, 1, 1, textGraphics);                   /* Permit write operations for planes */
	xstdvga_set_misc_graphics((!textGraphics) * VGA_MEM_MAP_32K_2, /* Set memory map (32K at 0xB8000 for text mode) */
							  1, textGraphics);

	/* Set color depth */
	U8 shift256 = colorDepth == D256 ? 1 : 0;
	xstdvga_set_graphics_mode(shift256, SAME, 1, SAME, SAME); 
	
    /* Set video resolution */
	if (height != AUTO)
		xstdcon_set_height(height);
}
