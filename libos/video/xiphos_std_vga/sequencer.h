#ifndef _XSTDVGA_SEQUENCER_H_
#define _XSTDVGA_SEQUENCER_H_


#include <define.h>
#include <io.h>

#include <include/attrs.h>
#include <include/types.h>


#define SET_SEQ_REG_FUNCTION(index, calcFunc, ...)                              \
	xstdvga_select_sequencer_reg(index);                                        \
    U8 __reg_old = xstdvga_in_from_reg();                                       \
    U16 __port; __asm__ __volatile__ ( "mov %%dx, %0" : "=g"(__port) : : "dx"); \
    xstdvga_out_to_reg(__port, calcFunc(__reg_old, ##__VA_ARGS__))              \


static inline void
xstdvga_set_reset(const U8 sync,
				  const U8 async)
{
	xstdvga_select_sequencer_reg(VGA_RESET_INDEX);
	xstdvga_out_to_reg((U8) ((sync == 1 ? sync << 1 : 0) | (async == 1 ? async : 0)));
}

static __CONST__ U8
__calculate_character_map_select(const U8 charMapSel,
								 const U8 charSetA,
								 const U8 charSetB)
{
	return (charSetA == SAME ?
			    charMapSel & ((1 << VGA_CSAS2) | (3 << VGA_CSAS1))
			    :
			    ((charSetA & 3) << VGA_CSAS2) | ((charSetA & 4) << VGA_CSAS1)) |
		   (charSetB == SAME ?
			    charMapSel & ((1 << VGA_CSBS2) | (3 << VGA_CSBS1))
			    :
			    ((charSetB & 3) << VGA_CSBS2) | ((charSetB & 4) << VGA_CSBS1));
}

static inline void
xstdvga_set_character_map_select(const U8 charSetA,
								 const U8 charSetB)
{
	SET_SEQ_REG_FUNCTION(VGA_CHAR_MAP_SELECT_INDEX, __calculate_character_map_select,
						 charSetA, charSetB);
}
	
static inline __CONST__ U8
__calculate_map_mask(const U8 mapMask,
					 const U8 plane0,
					 const U8 plane1,
					 const U8 plane2,
					 const U8 plane3)
{
	return (plane0 == SAME ?
			    mapMask & (1 << VGA_PLANE_0)
			    :
			    plane0 << VGA_PLANE_0) |
		   (plane1 == SAME ?
			    mapMask & (1 << VGA_PLANE_1)
			    :
			    plane1 << VGA_PLANE_1) |
		   (plane2 == SAME ?
			    mapMask & (1 << VGA_PLANE_2)
			    :
			    plane2 << VGA_PLANE_2) |
		   (plane3 == SAME ?
			    mapMask & (1 << VGA_PLANE_3)
			    :
			    plane3 << VGA_PLANE_3);
}

static inline void
xstdvga_set_map_mask(const U8 plane0,
					 const U8 plane1,
					 const U8 plane2,
					 const U8 plane3)
{
	SET_SEQ_REG_FUNCTION(VGA_MAP_MASK_INDEX, __calculate_map_mask,
						 plane0, plane1, plane2, plane3);
}

static inline __CONST__ U8
__calculate_sequencer_mem_mode(const U8 memMode,
							   const U8 chain4,
							   const U8 oeDis,
							   const U8 extMem)
{
	return (chain4 == SAME ?
			    memMode & (1 << VGA_CHAIN4)
			    :
			    chain4 << VGA_CHAIN4) |
		    (oeDis == SAME ?
			    memMode & (1 << VGA_OE_DIS)
			    :
			    oeDis << VGA_OE_DIS)  |
		    (extMem == SAME ?
			    memMode & (1 << VGA_EXT_MEM)
			    :
			    extMem << VGA_EXT_MEM);
}

static inline void
xstdvga_set_sequencer_mem_mode(const U8 chain4,
							   const U8 oeDis,
							   const U8 extMem)
{
	SET_SEQ_REG_FUNCTION(VGA_SEQ_MEM_MODE_INDEX, __calculate_sequencer_mem_mode,
						 chain4, oeDis, extMem);
}

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

static inline void
xstdvga_set_clocking_mode()
{
	xstdvga_reset_sequencer(VGA_SYNC);

	/* WIP */
	
	xstdvga_reset_sequencer(VGA_ENABLE);
}
	

#endif /* ! _XSTDVGA_SEQUENCER_H_ */
