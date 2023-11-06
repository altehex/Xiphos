#ifndef _XSTDVGA_DEFINE_H_
#define _XSTDVGA_DEFINE_H_


#include <include/types.h>


/*
 *  --- Registers ---
 */

/* Attribute */
#define VGA_ATTRIBUTE_ADDRESS           (U16) 0x3C0
#define VGA_ATTRIBUTE_DATA_READ         (U16) 0x3C1
#define VGA_ATTRIBUTE_DATA_WRITE        (U16) 0x3C0

/* CRT controller */
#define VGA_CRT_CONTROLLER_COLOR_ADDRESS (U16) 0x3D4
#define VGA_CRT_CONTROLLER_COLOR_DATA    (U16) 0x3D5

#define     VGA_OVERFLOW_INDEX           (U8) 0x07

#define         VGA_VRS9    (U8) (1 << 7) /* Vertical Retrace Start */
#define         VGA_VDE9    (U8) (1 << 6) /* Vertical Display End */
#define         VGA_VT9     (U8) (1 << 5) /* Vertical Total */
#define         VGA_LC8     (U8) (1 << 4) /* Line Compare */
#define         VGA_SVB8    (U8) (1 << 3) /* Start Vertical Blinking */
#define         VGA_VRS8    (U8) (1 << 2)
#define         VGA_VDE8    (U8) (1 << 1)
#define         VGA_VT8     (U8) (1 << 0)

#define     VGA_MAX_SCANLINE_INDEX      (U8) 0x09
#define     VGA_V_DISPLAY_END_INDEX     (U8) 0x12

/* Graphics controller */
#define VGA_GRAPHICS_CONTROLLER_ADDRESS (U16) 0x3CE
#define VGA_GRAPHICS_CONTROLLER_DATA    (U16) 0x3CF

#define     VGA_SET_RESET_INDEX         (U8) 0x00
#define     VGA_ENABLE_SET_RESET_INDEX  (U8) 0x01
#define     VGA_COLOR_COMPARE_INDEX     (U8) 0x02
#define     VGA_DATA_ROTATE_INDEX       (U8) 0x03
#define     VGA_READ_MAP_SELECT_INDEX   (U8) 0x04
#define     VGA_GRAPHICS_MODE_INDEX     (U8) 0x05
#define     VGA_MISC_GRAPHICS_INDEX     (U8) 0x06

#define         VGA_MEM_MAP_SEL 2    /* Memory Map Select */
#define         VGA_CHAIN_OE    1    /* Chain Odd/Even */
#define         VGA_ALPHA_DIS   0    /* Alphanumeric Mode Disable */

#define     VGA_COLOR_DONT_CARE_INDEX   (U8) 0x07
#define     VGA_BIT_MASK_INDEX          (U8) 0x08

/* Color */
#define VGA_PEL_ADDRESS_READ            (U16) 0x3C7
#define VGA_PEL_ADDRESS_WRITE           (U16) 0x3C8
#define VGA_PEL_DATA                    (U16) 0x3C9

/* External registers */
#define VGA_MISC_OUT_READ               (U16) 0x3CC
#define VGA_MISC_OUT_WRITE              (U16) 0x3C2

#define     VGA_VSYNCP      7 /* Vertical Sync Polarity */
#define     VGA_HSYNCP      6 /* Horizontal Sync Polarity */
#define     VGA_OE_PAGE     5 /* Odd/Even Page Select */
#define     VGA_CLOCK_SEL   2
#define         VGA_CLOCK_25MHZ      0
#define         VGA_CLOCK_28MHZ      1
#define     VGA_RAM_EN      1 /* RAM Enable */
#define     VGA_IOAS        0 /* I/O Address Select */

#define VGA_INPUT_STATUS_0              (U16) 0x3C2

#define     VGA_SS          (U8) (1 << 4) /* Switch Sense */

#define VGA_INPUT_STATUS_1_COLOR        (U16) 0x3DA

#define     VGA_VRETRACE    (U8) (1 << 3) /* Vertical Retrace */
#define     VGA_DD          (U8) (1 << 0) /* Disable Display */

/* Sequencer */
#define VGA_SEQUENCER_ADDRESS           (U16) 0x3C4
#define VGA_SEQUENCER_DATA              (U16) 0x3C5

#define     VGA_MAP_MASK                (U8) 0x02


/* Misc */
#define VGA_MEM_BASE_0  0x000A0000
#define VGA_MEM_BASE_1  0x000B0000
#define VGA_MEM_BASE_2  0x000B8000
#define VGA_PLANE_SZ    0x00010000

#define VGA_MEM_MAP_128K    0
#define VGA_MEM_MAP_64K     1
#define VGA_MEM_MAP_32K_1   2
#define VGA_MEM_MAP_32K_2   3

#define VGA_PLANE_0   0
#define VGA_PLANE_1   1
#define VGA_PLANE_2   2
#define VGA_PLANE_3   3

#define SAME      255 /*  Is used to specify whether    
					   *  a bit in a register should be
					   *  changed.
					   */

							  

#endif /* ! _XSTDVGA_DEFINE_H_ */
