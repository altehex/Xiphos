#ifndef _XSTDVGA_GRAPHICS_H_
#define _XSTDVGA_GRAPHICS_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


#define SET_GRAPHICS_REG_FUNCTION(index, calcFunc, ...)                         \
	xstdvga_select_graphics_reg(index);                                         \
    U8 __reg_old = xstdvga_in_from_reg();                                       \
    U16 __port; __asm__ __volatile__ ( "mov %%dx, %0" : "=g"(__port) : : "dx"); \
    xstdvga_out_to_reg(__port, calcFunc(__reg_old, ##__VA_ARGS__))              \


static __CONST__ U8
__calculate_graphics_mode(const U8 gMode,
						  const U8 shift256,
						  const U8 shiftReg,
						  const U8 hostOe,
						  const U8 readMode,
						  const U8 writeMode)
{
	return (shift256 == SAME ?
			    gMode & (1 << VGA_SHIFT_256)
			    :
			    shift256 << VGA_SHIFT_256) |
		   (shiftReg == SAME ?
			    gMode & (1 << VGA_SHIFT_REG)
			    :
			    shiftReg << VGA_SHIFT_REG) |
		   (hostOe == SAME ?
			    gMode & (1 << VGA_HOST_OE)
			    :
			    hostOe << VGA_HOST_OE)     |
		   (readMode == SAME ?
			    gMode & (1 << VGA_READ_MODE)
			    :
			    readMode << VGA_READ_MODE) |
		   (writeMode == SAME ?
			    gMode & (3 << VGA_WRITE_MODE)
			    :
			    writeMode << VGA_WRITE_MODE);
}

static inline void
xstdvga_set_graphics_mode(const U8 shift256,
						  const U8 shiftReg,
						  const U8 hostOe,
						  const U8 readMode,
						  const U8 writeMode)
{
	SET_GRAPHICS_REG_FUNCTION(VGA_GRAPHICS_MODE_INDEX, __calculate_graphics_mode,
							  shift256, shiftReg, hostOe, readMode, writeMode);
}

static __CONST__ U8
__calculate_misc_graphics(const U8 miscGraphics,
						  const U8 memMapSel,
						  const U8 chainOe,
						  const U8 alphanumDis)
{
	return (memMapSel == SAME ?
			    miscGraphics & (1 << VGA_MEM_MAP_SEL)
			    :
			    memMapSel << VGA_MEM_MAP_SEL) |
		   (chainOe == SAME ?
			    miscGraphics & (1 << VGA_CHAIN_OE)
			    :
			    chainOe << VGA_CHAIN_OE)   |
		   (alphanumDis == SAME ?
			    miscGraphics & (1 << VGA_ALPHANUM_DIS)
			    :
			    alphanumDis << VGA_ALPHANUM_DIS);
}
	
static inline void
xstdvga_set_misc_graphics(const U8 memMapSel,
						  const U8 chainOe,
						  const U8 alphanumDis)
{
	SET_GRAPHICS_REG_FUNCTION(VGA_MISC_GRAPHICS_INDEX, __calculate_misc_graphics,
							  memMapSel, chainOe, alphanumDis);
}


#endif /* ! _XSTDVGA_GRAPHICS_H_ */
