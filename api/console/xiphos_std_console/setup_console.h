#ifndef _XSTDCON_SETUP_CONSOLE_H_
#define _XSTDCON_SETUP_CONSOLE_H_


#include <include/attrs.h>

#include <libos/video/xiphos_std_vga/xiphos_std_vga.h>

#include <font.h>
#include <mode.h>


static inline __ALWAYS_INLINE__ void
xstdcon_setup_console()
{
	xstdcon_set_mode(&G360x480x256);
	xstdcon_set_font();	
}

void __ALIAS__(xstdcon_setup_console) __WEAK__
setup_console();


#endif /* ! _XSTDCON_SETUP_CONSOLE_H_ */
