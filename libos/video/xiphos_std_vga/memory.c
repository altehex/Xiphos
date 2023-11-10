#include "memory.h"

#include <define.h>
#include <graphics.h>

#include <include/types.h>


U64
xstdvga_get_mem_base()
{
	xstdvga_select_graphics_reg(VGA_MISC_GRAPHICS_INDEX);
	U8 memMap = xstdvga_in_from_reg() >> 2;
	
	switch (memMap) {
		case VGA_MEM_MAP_32K_1:
			return VGA_MEM_BASE_1;
		case VGA_MEM_MAP_32K_2:
			return VGA_MEM_BASE_2;
		default:
			return VGA_MEM_BASE_0;
	}
}
