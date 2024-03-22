
#ifndef _XSTDMALLOC_FREE_LIST_H_
#define _XSTDMALLOC_FREE_LIST_H_


#include <attrs.h>
#include <types.h>

#include <stdatomic.h>


#define XSMFL_BIG_ALLOC_THRESHOLD  1024


typedef struct _xsmfl_MemRegion xsmfl_MemRegion;
struct __PACKED__
_xsmfl_MemRegion {
	U64                sz;
	xsmfl_MemRegion *  next;
	xsmfl_MemRegion *  prev;
};


extern xsmfl_MemRegion *  xsmfl_freeMemRegions; /* Points to the first free region, order is important here */
extern xsmfl_MemRegion *  xsmfl_usedMemRegions; /* Points to the last allocated region */

extern xsmfl_MemRegion xsmfl_sentinelRegion;


#define XSMFL_LOCK_LISTS                              \
    while (atomic_flag_test_and_set(&xsmfl_listLock)) \
		pause();

#define XSMFL_UNLOCK_LISTS \
    atomic_flag_clear(&xsmfl_listLock);


extern volatile atomic_flag xsmfl_listLock;


#endif /* ! _XSTDMALLOC_FREE_LIST_H_ */
