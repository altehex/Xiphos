#include "memory.h"


#include "attrs.h"
#include <define.h>
#include <graphics.h>

#include <include/types.h>


void
xstdvga_clear_plane(U8 planeNum)
{
	register U64 planeBase __asm__ ("rdi") = VGA_MEM_BASE_0 + (planeNum * VGA_PLANE_SZ);
	register U64 planeSz __asm__ ("rcx") = VGA_PLANE_SZ / 8;
		
	__asm__ __volatile__
	(
	    "xor     %%rax, %%rax;"
		"rep stosq"
    :
	: "r"(planeSz), "r"(planeBase)
	: "rax");
}


U64
xstdvga_get_mem_base()
{
	xstdvga_select_graphics_reg(VGA_MISC_GRAPHICS_INDEX);
	U8 memMap = xstdvga_in_from_graphics_reg() >> 2;
	
	switch (memMap) {
		case VGA_MEM_MAP_32K_1:
			return VGA_MEM_BASE_1;
		case VGA_MEM_MAP_32K_2:
			return VGA_MEM_BASE_2;
		default:
			return VGA_MEM_BASE_0;
	}
}
