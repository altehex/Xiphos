#ifndef _XSTDVGA_MEMORY_H_
#define _XSTDVGA_MEMORY_H_


#include "attrs.h"
#include <define.h>
#include <graphics.h>

#include <include/types.h> 


__LIBOS_XSTDVGA__ void xstdvga_clear_plane(U8);
__LIBOS_XSTDVGA__ U64 xstdvga_get_mem_base();


static inline void
xstdvga_set_mem_map(U8 memMap)
{
	xstdvga_set_misc_graphics(memMap, SAME, SAME);
}


#endif /* ! _XSTDVGA_MEMORY_H_ */
