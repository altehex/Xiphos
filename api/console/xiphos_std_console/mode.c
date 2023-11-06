#include <mode.h>

#include <include/types.h>

#include <libos/video/xiphos_std_vga/xiphos_std_vga.h>


VgaGraphicsMode
xstdcon_get_mode()
{
	VgaGraphicsMode currMode;

	/* WIP */
	
	return currMode;
}

void
xstdcon_set_mode_mparm(U16 height,
					   U16 width,
					   U8  colorDepth,
					   U8  symbolSz)
{
	xstdcon_set_symbol_sz(symbolSz);
	xstdcon_set_height(height);
}
