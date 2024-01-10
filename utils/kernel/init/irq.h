#ifndef _IRQ_H_
#define _IRQ_H_


#include <attrs.h>
#include <types.h>


#define IDT_ENTRY_NUM   256


typedef struct __PACKED__ {
	U16     offsetLow;
	U16     sel;
	U8      ist;
	U8      type;
	U16     offsetMid;
	U32     offsetHigh;
	U32     _res;
} Gate64;

typedef struct __PACKED__ {
	U16     sz;
	void *  base;
} IDTR;

static Gate64 __UNUSED__ idt[IDT_ENTRY_NUM];
static IDTR __UNUSED__ idtr;


static inline void
__set_gate(Gate64 * entry,
		   void    (*offset)(),
		   U8       type)
{
	entry->offsetLow  = (U64)offset & 0xFFFF;
	/* entry->sel        = getCodeSeg(); */
	entry->ist        = 0;
	entry->type       = type;
	entry->offsetMid  = ((U64)offset >> 16) & 0xFFFF;
	entry->offsetHigh = ((U64)offset >> 32) & 0xFFFFFFFF00000000;
	entry->_res       = 0;
}


void __KINIT_IRQ__
setup_irqs(void);


#endif /* ! _IRQ_H_ */
