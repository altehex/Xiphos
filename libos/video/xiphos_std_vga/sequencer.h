#ifndef _XSTDVGA_SEQUENCER_H_
#define _XSTDVGA_SEQUENCER_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


static __CONST__ U8
__calculate_map_mask(const U8 mapMask,
					 const U8 plane0,
					 const U8 plane1,
					 const U8 plane2,
					 const U8 plane3)
{
	return (plane0 == SAME ?
			    mapMask & (1 << VGA_PLANE_0)
			    :
			    plane0 << VGA_PLANE_0) |
		   (plane1 == SAME ?
			    mapMask & (1 << VGA_PLANE_1)
			    :
			    plane1 << VGA_PLANE_1) |
		   (plane2 == SAME ?
			    mapMask & (1 << VGA_PLANE_2)
			    :
			    plane2 << VGA_PLANE_2) |
		   (plane3 == SAME ?
			    mapMask & (1 << VGA_PLANE_3)
			    :
			    plane3 << VGA_PLANE_3);
}

static inline void
xstdvga_set_map_mask(const U8 plane0,
					 const U8 plane1,
					 const U8 plane2,
					 const U8 plane3)
{
	xstdvga_select_sequencer_reg(VGA_MAP_MASK);
	U8 mapMask = xstdvga_in_from_sequencer_reg();
	xstdvga_out_to_sequencer_reg(__calculate_map_mask(mapMask, plane0,
													  plane1, plane2, plane3));
}


#endif /* ! _XSTDVGA_SEQUENCER_H_ */
