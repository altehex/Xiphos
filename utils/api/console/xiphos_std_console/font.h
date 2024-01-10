#ifndef _XSTDCON_FONT_H_
#define _XSTDCON_FONT_H_


#include "attrs.h"

#include <include/types.h>

#include <xiphos_std_vga.h>


void __API_XSTDCON__
xstdcon_get_font();
void __API_XSTDCON__
xstdcon_set_font();


static inline void
xstdcon_set_symbol_sz(U8 sz)
{
	xstdvga_set_max_scanline(sz - 1);
}


#endif /* !_XSTDCON_FONT_H_ */
