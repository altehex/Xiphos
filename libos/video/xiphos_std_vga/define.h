/* Constants and macros for Xiphos standard VGA */

#ifndef _XIPHOS_STD_VGA_DEFINE_H_
#define _XIPHOS_STD_VGA_DEFINE_H_

/*
 *  --- Registers ---
 */

/* Attribute */
#define VGA_ATTRIBUTE_ADDRESS           0x3C0
#define VGA_ATTRIBUTE_DATA_READ         0x3C1
#define VGA_ATTRIBUTE_DATA_WRITE        0x3C0

/* CRT controller */
#define VGA_CRT_CONTROLLER_COLOR_ADDRESS 0x3D4
#define VGA_CRT_CONTROLLER_COLOR_DATA    0x3D5
#define VGA_CRT_CONTROLLER_MONO_ADDRESS 0x3B4
#define VGA_CRT_CONTROLLER_MONO_DATA    0x3B5

/* Graphics controller */
#define VGA_GRAPHICS_CONTROLLER_ADDRESS 0x3CE
#define VGA_GRAPHICS_CONTROLLER_DATA    0x3CF

#define VGA_BIT_MASK_INDEX              0x08
#define VGA_DATA_ROTATE_INDEX           0x03
#define VGA_ENABLE_SET_RESET_INDEX      0x01
#define VGA_GRAPHICS_MODE_INDEX         0x05
#define VGA_SET_RESET_INDEX             0x00

/* Color */
#define VGA_PEL_ADDRESS_READ            0x3C7
#define VGA_PEL_ADDRESS_WRITE           0x3C8
#define VGA_PEL_DATA                    0x3C9

/* External registers */
#define VGA_MISC_OUT_READ_PORT          0x3C2
#define VGA_MISC_OUT_WRITE_PORT         0x3CC

/* Sequencer */
#define VGA_SEQUENCER_ADDRESS           0x3C4
#define VGA_SEQUENCER_DATA              0x3C5

/* Status */
#define VGA_INPUT_STATUS_1              0x3DA


#endif /* ! _XIPHOS_STD_VGA_DEFINE_H_ */
