#ifndef _XSTDVGA_GRAPHICS_H_
#define _XSTDVGA_GRAPHICS_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


/* Registers */
#define GRAPHICS_CTRL_ADDRESS (U16) 0x3CE
#define GRAPHICS_CTRL_DATA    (U16) 0x3CF


enum GraphicsIndex {
	SET_RESET,
	ENABLE_SET_RESET,
	COLOR_COMPARE,
	DATA_ROTATE,
	READ_MAP_SELECT,
	GRAPHICS_MODE,
	MISC_GRAPHICS,
	COLOR_DONT_CARE,
	BIT_MASK
};


#define SET_GRAPHICS_REG_FUNCTION(INDEX, ...) \
	SET_REG_ADDR_DATA(GRAPHICS_CTRL_ADDRESS, INDEX, ##__VA_ARGS__)


/* Leave the HOE as is */
#define S256_BIT    BIT6
#define SR_BIT      BIT5
#define HOE_BIT     BIT4
#define RM_BIT      BIT3
#define WM_BIT      BIT1 | BIT1

#define GRAPHICS_MODE_MASK1(S256, SR, HOE, RM, WM) \
	(S256 == SAME ? S256_BIT : 0) |                \
	(SR   == SAME ? SR_BIT   : 0) |                \
	(HOE  == SAME ? HOE_BIT  : 0) |                \
	(RM   == SAME ? RM_BIT   : 0) |                \
	(WM   == SAME ? WM_BIT   : 0)

#define GRAPHICS_MODE_MASK2(S256, SR, HOE, RM, WM) \
	(S256 != SAME ? S256 << 6 : 0) |               \
	(SR   != SAME ? SR << 5   : 0) |               \
	(HOE  != SAME ? HOE << 4  : 0) |               \
	(RM   != SAME ? RM << 3   : 0) |               \
	(WM   != SAME ? WM        : 0)

/* 
 *  Changes value of Graphics Mode register of the graphics controller.
 *--------------------------------------------------------------------*
 */
static inline void
xstdvga_set_graphics_mode(const U8 shift256,
						  const U8 shiftReg,
						  const U8 hostOe,
						  const U8 readMode,
						  const U8 writeMode)
{
	SET_GRAPHICS_REG_FUNCTION(GRAPHICS_MODE, shift256, shiftReg,
							  hostOe, readMode, writeMode);
}

#define MMSEL_BIT   BIT3 | BIT2
#define COE_BIT     BIT1
#define ADIS_BIT    BIT0

#define MISC_GRAPHICS_MASK1(MMSEL, COE, ADIS) \
	(MMSEL == SAME ? MMSEL_BIT : 0) |         \
	(COE   == SAME ? COE_BIT   : 0) |         \
	(ADIS  == SAME ? ADIS_BIT  : 0)

#define MISC_GRAPHICS_MASK2(MMSEL, COE, ADIS) \
	(MMSEL != SAME ? MMSEL << 2 : 0) |        \
	(COE   != SAME ? COE << 1   : 0) |        \
	(ADIS  != SAME ? ADIS       : 0)

#define VGA_MEM_MAP_128K    0
#define VGA_MEM_MAP_64K     1
#define VGA_MEM_MAP_32K_1   2
#define VGA_MEM_MAP_32K_2   3

#define VGA_TEXT_MODE       0
#define VGA_GRAPHICS_MODE   1

/* 
 *  Changes value of Miscellaneous Graphics register of the graphics controller.
 *--------------------------------------------------------------------*
 *  memMapSel:   Memory Map Select is the range of host memory addresses decoded by VGA and
 *               mapped into display memory accesses. The options are:
 *               - VGA_MEM_MAP_128K  (0xA0000-0xBFFFF)
 *               - VGA_MEM_MAP_64K   (0xA0000-0xAFFFF)
 *               - VGA_MEM_MAP_32K_1 (0xB0000-0xB7FFF)
 *               - VGA_MEM_MAP_32K_2 (0xB8000-0xBFFFF)
 *  chainOe:     Chain Odd/Even Enable. Selects odd (1) or even (0) map by replacing A0 bit
 *               with a higher-order bit.
 *  alphanumDis: Alphanumeric Mode Disable. When set to 1, this bit selects graphics modes,
 *               which also disables the character generator latches. Use the VGA_TEXT_MODE
 *               and VGA_GRAPHICS_MODE constants.
 */ 	
static inline void
xstdvga_set_misc_graphics(const U8 memMapSel,
						  const U8 chainOe,
						  const U8 alphanumDis)
{
	SET_GRAPHICS_REG_FUNCTION(MISC_GRAPHICS, memMapSel, chainOe, alphanumDis);
}


#endif /* ! _XSTDVGA_GRAPHICS_H_ */
