#include <crt.h>

#include <define.h>

#include <include/asm.h>
#include <include/types.h>


void
xstdvga_set_max_scanline(U8 maxScanline)
{
	/* in() */
	out(VGA_CRT_CONTROLLER_COLOR_ADDRESS, VGA_MAX_SCANLINE_INDEX);

	out(VGA_CRT_CONTROLLER_COLOR_DATA, maxScanline);
}
