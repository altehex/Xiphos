#ifndef _XSTDCON_MODE_H_
#define _XSTDCON_MODE_H_


#include "attrs.h"

#include <include/attrs.h>
#include <include/types.h>

#include <libos/video/xiphos_std_vga/xiphos_std_vga.h>


/* Color depth in bits */
#define D2    1
#define D16   4
#define D256  8
#define D32K  15
#define D64K  16
#define D16M  24

/* Symbol size */
#define SYMBOL_SIZE_DEFAULT   8    


typedef const struct __PACKED__ {
	U16     height;
	U16     width;
	U8      colorDepth;
} VgaGraphicsMode;

/* VGA modes */
static VgaGraphicsMode G320x200x16    = { .height = 320,  .width = 200, .colorDepth = D16 };
static VgaGraphicsMode G640x200x16    = { .height = 640,  .width = 200, .colorDepth = D16 };
static VgaGraphicsMode G640x350x16    = { .height = 640,  .width = 350, .colorDepth = D16 };
static VgaGraphicsMode G640x480x16    = { .height = 640,  .width = 480, .colorDepth = D16 };
static VgaGraphicsMode G320x200x256   = { .height = 320,  .width = 200, .colorDepth = D256 };
static VgaGraphicsMode G320x240x256   = { .height = 320,  .width = 240, .colorDepth = D256 };
static VgaGraphicsMode G320x400x256   = { .height = 320,  .width = 400, .colorDepth = D256 };
static VgaGraphicsMode G360x480x256   = { .height = 360,  .width = 480, .colorDepth = D256 };
static VgaGraphicsMode G640x480x2     = { .height = 640,  .width = 480, .colorDepth = D2 };

/* SVGA modes */
static VgaGraphicsMode G640x480x256   = { .height = 640,  .width = 480,  .colorDepth = D256 };
static VgaGraphicsMode G800x600x256   = { .height = 800,  .width = 600,  .colorDepth = D256 };
static VgaGraphicsMode G1024x768x256  = { .height = 1024, .width = 768,  .colorDepth = D256 };
static VgaGraphicsMode G1280x1024x256 = { .height = 1280, .width = 1024, .colorDepth = D256 };
static VgaGraphicsMode G320x200x32K   = { .height = 320,  .width = 200,  .colorDepth = D32K };
static VgaGraphicsMode G320x200x64K   = { .height = 320,  .width = 200,  .colorDepth = D64K };
static VgaGraphicsMode G320x200x16M   = { .height = 320,  .width = 200,  .colorDepth = D16M };
static VgaGraphicsMode G640x480x32K   = { .height = 640,  .width = 480,  .colorDepth = D32K };
static VgaGraphicsMode G640x480x64K   = { .height = 640,  .width = 480,  .colorDepth = D64K };
static VgaGraphicsMode G640x480x16M   = { .height = 640,  .width = 480,  .colorDepth = D16M };
static VgaGraphicsMode G800x600x32K   = { .height = 800,  .width = 600,  .colorDepth = D32K };
static VgaGraphicsMode G800x600x64K   = { .height = 800,  .width = 600,  .colorDepth = D64K };
static VgaGraphicsMode G800x600x16M   = { .height = 800,  .width = 600,  .colorDepth = D16M };
static VgaGraphicsMode G1024x768x32K  = { .height = 1024, .width = 768,  .colorDepth = D32K };
static VgaGraphicsMode G1024x768x64K  = { .height = 1024, .width = 768,  .colorDepth = D64K };
static VgaGraphicsMode G1024x768x16M  = { .height = 1024, .width = 768,  .colorDepth = D16M };
static VgaGraphicsMode G1280x1024x32K = { .height = 1280, .width = 1024, .colorDepth = D32K };
static VgaGraphicsMode G1280x1024x64K = { .height = 1280, .width = 1024, .colorDepth = D64K };
static VgaGraphicsMode G1280x1024x16M = { .height = 1280, .width = 1024, .colorDepth = D16M };

VgaGraphicsMode __API_XSTDCON__
xstdcon_get_mode();
void __API_XSTDCON__
xstdcon_set_mode_mparm(U16, U16, U8, U8);

/* Inlined because it just sets up the args for xstdcon_set_mode_mparm */
inline void
xstdcon_set_mode_struct(VgaGraphicsMode * mode)
{
	xstdcon_set_mode_mparm(mode->height,
						   mode->width,
						   mode->colorDepth,
						   SYMBOL_SIZE_DEFAULT);
}


#define xstdcon_set_mode(_1, ...)  _Generic((_1), \
											VgaGraphicsMode *: xstdcon_set_mode_struct, \
											U16:               xstdcon_set_mode_mparm) (_1, ##__VA_ARGS__)

inline void
xstdcon_set_symbol_sz(sz)
{
	xstdvga_set_max_scanline(sz - 1);
}
		

#endif /* !_XSTDCON_MODE_H_ */
