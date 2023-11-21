#ifndef _XSTDMALLOC_FREE_LIST_H_
#define _XSTDMALLOC_FREE_LIST_H_


#include <attrs.h>
#include <types.h>

#include <mem/init.h>


typedef struct _MemRegion MemRegion;

struct __PACKED__
_MemRegion {
	U16         canary; /* To be used */
	U16         flags;
	U64         sz;
	MemRegion * next;
	MemRegion * prev;
};


/* Don't use volatile here (these are used only on startup with one thread anyway) */
static __USED__ MemRegion * freeMemRegions;
static __USED__ MemRegion * usedMemRegions;

static MemRegion            __sentinelRegion = { 0, 0, 0, 0, 0 };
static __USED__ MemRegion * sentinelRegion   = &__sentinelRegion;


#endif /* ! _XSTDMALLOC_FREE_LIST_H_ */
