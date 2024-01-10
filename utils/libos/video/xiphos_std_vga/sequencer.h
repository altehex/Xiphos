#ifndef _XSTDVGA_SEQUENCER_H_
#define _XSTDVGA_SEQUENCER_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


#define SEQUENCER_ADDRESS           (U16) 0x3C4
#define SEQUENCER_DATA              (U16) 0x3C5


enum SeqIndex {
	RESET,
	CLOCK_MODE,
	MAP_MASK,
	CHAR_MAP_SELECT,
	SEQUENCER_MEMORY_MODE
};


#define SET_SEQ_REG_FUNCTION(INDEX, ...) \
	SET_REG_ADDR_DATA(SEQUENCER_ADDRESS, INDEX, ##__VA_ARGS__)


/* 
 *  Changes value of Reset register of the sequencer.
 *--------------------------------------------------------------------*/ 
static inline void
xstdvga_set_reset(const U8 sync,
				  const U8 async)
{
	xstdvga_select_reg(SEQUENCER_ADDRESS, RESET);
	xstdvga_out_to_reg((U8) ((sync == 1 ? sync << 1 : 0) | (async == 1 ? async : 0)));
}

#define VGA_SYNC    0
#define VGA_ASYNC   1
#define VGA_ENABLE  255

/* 
 *  Resets or enables the sequencer. Only used in xstdvga_set_clock_mode().
 *--------------------------------------------------------------------*
 *  Use VGA_SYNC and VGA_ASYNC for synchronous and asynchronous resetting
 *  correspondingly. Any other value enables the sequencer (VGA_ENABLE is
 *  just for clarity).
 */
static inline void
xstdvga_reset_sequencer(U8 syncAsync)
{
	switch (syncAsync) {
		case VGA_SYNC: {
			xstdvga_set_reset(0, 1);
			break;
		}
		case VGA_ASYNC: {
			xstdvga_set_reset(1, 0);
			break;
		}
		default:
			xstdvga_set_reset(1, 1);
	}
}

/* 
 *  Changes value of Clocking Mode register of the sequencer. (WIP)
 *--------------------------------------------------------------------*/ 
static inline void
xstdvga_set_clock_mode()
{
	xstdvga_reset_sequencer(VGA_SYNC);

	/* WIP. Just  */
	
	xstdvga_reset_sequencer(VGA_ENABLE);
}

#define CSAS_BIT    BIT5 | BIT3 | BIT2
#define CSBS_BIT    BIT4 | BIT1 | BIT0

#define CHAR_MAP_SELECT_MASK1(CSAS, CSBS) \
	(CSAS == SAME ? CSAS_BIT : 0 ) |      \
	(CSBS == SAME ? CSBS_BIT : 0 )

#define CHAR_MAP_SELECT_MASK2(CSAS, CSBS)                                        \
	(CSAS != SAME ? ((CSAS & BIT2) << 5) | ((CSAS & (BIT1 | BIT0)) << 2) : 0 ) | \
	(CSBS != SAME ? ((CSBS & BIT2) << 4) | (CSBS & (BIT1 | BIT0))        : 0 )

#define  VGA_FONT_AT_0000    0
#define  VGA_FONT_AT_4000    1
#define  VGA_FONT_AT_8000    2
#define  VGA_FONT_AT_C000    3
#define  VGA_FONT_AT_2000    4
#define  VGA_FONT_AT_6000    5
#define  VGA_FONT_AT_A000    6
#define  VGA_FONT_AT_E000    7

/* 
 *  Changes value of Character Map Select register of the sequencer.
 *--------------------------------------------------------------------*
 *  charSetA: Character Set A is used when bit 3 of the attribute
 *            byte for a character is set to 1.
 *  charSetB: Character Set B is used when bit 3 of the attribute
 *            byte for a character is set to 0.
 *  Use VGA_FONT_AT_<offset> constants defined in sequencer.h.
 */ 
static inline void
xstdvga_set_character_map_select(const U8 charSetA,
								 const U8 charSetB)
{
	SET_SEQ_REG_FUNCTION(CHAR_MAP_SELECT, charSetA, charSetB);
}

#define MAP_MASK_MASK1(P0, P1, P2, P3) \
	(P0 == SAME ? BIT0 : 0) |          \
	(P1 == SAME ? BIT1 : 0) |          \
	(P2 == SAME ? BIT2 : 0) |          \
	(P3 == SAME ? BIT3 : 0)

#define MAP_MASK_MASK2(P0, P1, P2, P3) \
	(P0 != SAME ? P0      : 0) |       \
	(P1 != SAME ? P1 << 1 : 0) |       \
	(P2 != SAME ? P2 << 2 : 0) |       \
	(P3 != SAME ? P3 << 3 : 0)	

static inline void
xstdvga_set_map_mask(const U8 plane0,
					 const U8 plane1,
					 const U8 plane2,
					 const U8 plane3)
{
	SET_SEQ_REG_FUNCTION(MAP_MASK, plane0, plane1, plane2, plane3);
}

#define C4_BIT       BIT3
#define OEDIS_BIT    BIT2
#define EXTMEM_BIT   BIT1

#define SEQUENCER_MEMORY_MODE_MASK1(C4, OEDIS, EXTMEM) \
	(C4     == SAME? C4_BIT     : 0) |                 \
	(OEDIS  == SAME? OEDIS_BIT  : 0) |                 \
	(EXTMEM == SAME? EXTMEM_BIT : 0)

#define SEQUENCER_MEMORY_MODE_MASK2(C4, OEDIS, EXTMEM) \
	(C4     != SAME? C4 << 3     : 0) |                \
	(OEDIS  != SAME? OEDIS << 2  : 0) |                \
	(EXTMEM != SAME? EXTMEM << 1 : 0)

/* 
 *  Changes value of Character Map Select register of the sequencer.
 *--------------------------------------------------------------------*
 */ 
static inline void
xstdvga_set_sequencer_mem_mode(const U8 chain4,
							   const U8 oeDis,
							   const U8 extMem)
{
	SET_SEQ_REG_FUNCTION(SEQUENCER_MEMORY_MODE, chain4, oeDis, extMem);
}


#endif /* ! _XSTDVGA_SEQUENCER_H_ */
