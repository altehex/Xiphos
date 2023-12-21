#ifndef _XSTDVGA_SETUP_VIDEO_H_
#define _XSTDVGA_SETUP_VIDEO_H_


#include <crt.h>
#include <define.h>
#include <external.h>
#include <sequencer.h>

#include <include/attrs.h>


void * xstdvga_pci_detect_vga();

__WEAK__ void * pci_detect_vga();


/*
 *  VGA hardware set up on boot
 *---------------------------------------------------------*/
static inline void
xstdvga_setup_video()
{
/* Inlined because it should be called one time at startup */
	xstdvga_set_vertical_retrace_end(0, SAME, SAME);    /* Permit write operations to CRT registers 0-7 */
	xstdvga_set_sequencer_mem_mode(SAME, SAME, 1);      /* Enable extended memory */
	xstdvga_set_misc_out(SAME, SAME, SAME, SAME, 1, 1); /* Enable access to display buffer, color mode */
}

static inline void __ALIAS__(xstdvga_setup_video)
setup_video();


#endif /* _XSTDVGA_SETUP_VIDEO_H_ */
