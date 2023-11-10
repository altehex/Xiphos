#ifndef _XSTDVGA_SETUP_VIDEO_H_
#define _XSTDVGA_SETUP_VIDEO_H_


#include <define.h>
#include <graphics.h>
#include <memory.h>
#include <sequencer.h>

/*
 *  VGA hardware set up on boot
 *---------------------------------------------------------*
 *  textGraphics: 1 for text mode
 */
static inline void
xstdvga_setup_video()
{
/* Inlined because it should be called one time at startup */
	
	xstdvga_set_vertical_retrace(0, SAME, SAME);     /* Permit write operations to CRT registers 0-7 */
	xstdvga_set_sequencer_mem_mode(SAME, SAME, 1);   /* Enable extended memory */
	xstdvga_set_misc_out(SAME, SAME, SAME, SAME, 1, 1); /* Enable access to display buffer, color mode */
	while(1){}
}

static inline void __ALIAS__(xstdvga_setup_video)
libos_setup_video();


#endif /* _XSTDVGA_SETUP_VIDEO_H_ */
