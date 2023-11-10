#ifndef _XSTDCON_SETUP_CONSOLE_H_
#define _XSTDCON_SETUP_CONSOLE_H_


#include <font.h>
#include <mode.h>

#include <xiphos_std_vga.h>

#include <include/attrs.h>


/* Inlined because it should be called one time at startup */
static inline void
xstdcon_setup_boot_stdout()
{
	libos_setup_video();
	xstdcon_set_mode(&xiphosDebugTextMode); 
	xstdcon_set_font(/* FONT */);	
}

static inline void __ALIAS__(xstdcon_setup_boot_stdout)
api_setup_boot_stdout();


#endif /* ! _XSTDCON_SETUP_CONSOLE_H_ */
