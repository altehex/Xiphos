#ifndef _XSTDCON_SETUP_CONSOLE_H_
#define _XSTDCON_SETUP_CONSOLE_H_


#include <mode.h>

#include <xiphos_std_vga.h>

#include <include/attrs.h>


static inline void
xstdcon_setup_boot_stdout()
{
/* Inlined because it should be called one time at startup */

	pci_detect_vga();
	setup_video(); /* Basic video setting */
	xstdcon_set_mode_boot_stdout(); 
}

static inline void __ALIAS__(xstdcon_setup_boot_stdout)
setup_boot_stdout();


#endif /* ! _XSTDCON_SETUP_CONSOLE_H_ */
