#ifndef _XSTDCON_SETUP_CONSOLE_H_
#define _XSTDCON_SETUP_CONSOLE_H_


#include <font.h>
#include <mode.h>

#include <libos/video/xiphos_std_vga/xiphos_std_vga.h>

#include <include/attrs.h>


/* Inlined because it should be called one time at startup */
static inline void
xstdcon_setup_console()
{
	xstdcon_set_mode(&G360x480x256); /* Change to SELECTED_VIDEO_MODE */
	xstdcon_set_font(/* FONT */);	
}

static inline void __ALIAS__(xstdcon_setup_console)
api_setup_console();


#endif /* ! _XSTDCON_SETUP_CONSOLE_H_ */
