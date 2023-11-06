#ifndef _XSTDVGA_SETUP_VIDEO_H_
#define _XSTDVGA_SETUP_VIDEO_H_


#include <define.h>
#include <memory.h>
#include <sequencer.h>


/* Inlined because it should be called one time at startup */
static inline U32
xstdvga_setup_video()
{
	/* Permit write operations for every plane */
	xstdvga_set_map_mask(1, 1, 1, 1);

	/* Clear all planes */
	for (int planeNum = VGA_PLANE_0; planeNum <= VGA_PLANE_3; planeNum++)
		xstdvga_clear_plane(planeNum);
	
	while (1) {}
	
	return xstdvga_get_mem_base();
}

static inline void __ALIAS__(xstdvga_setup_video)
libos_setup_video();


#endif /* _XSTDVGA_SETUP_VIDEO_H_ */
