#ifndef _XSTDCON_MODE_H_
#define _XSTDCON_MODE_H_


#include "attrs.h"

#include <include/attrs.h>
#include <include/types.h>

#include <xiphos_std_vga.h>


/* Color depth in bits */
#define D2    1
#define D16   4
#define D256  8
#define D32K  15
#define D64K  16
#define D16M  24

#define TEXT      0
#define GRAPHICS  1

#define AUTO (U16) -1 

#define SYMBOL_SIZE_DEFAULT   8    


typedef struct __PACKED__ {
	U16     height;
	U16     width;
	U8      colorDepth;
	U8      graphics;       /* True for graphics mode */
} xstdcon_VgaMode;

	
__API_XSTDCON__ void 
xstdcon_set_mode_mparm(const U16, const U16, const U8, const U8);


/* Inlined because it just sets up the args for xstdcon_set_mode_mparm */
static inline void
xstdcon_set_mode_struct(const xstdcon_VgaMode * mode)
{
	xstdcon_set_mode_mparm(mode->height,
						   mode->width,
						   mode->colorDepth,
						   mode->graphics);
}

#define xstdcon_set_mode(_1, ...)  _Generic((_1), \
											xstdcon_VgaMode *: xstdcon_set_mode_struct, \
											U16:               xstdcon_set_mode_mparm) (_1, ##__VA_ARGS__)

static inline void
xstdcon_set_height(U16 height)
{
	xstdvga_set_v_display(height - 1);
}

/*
 *  Does a fast mode setting for stdout console at boot
 */
static inline void
xstdcon_set_mode_boot_stdout()
{
	
}
		

#endif /* !_XSTDCON_MODE_H_ */
