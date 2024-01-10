#ifndef _XSTDMALLOC_FREE_LIST_H_
#define _XSTDMALLOC_FREE_LIST_H_


#include <attrs.h>
#include <types.h>

#include <mem/init.h>

#include <stdatomic.h>


#define BIG_ALLOC_THRESHOLD     1024


typedef struct _MemRegion MemRegion;


struct __PACKED__
_MemRegion {
	U64         sz;
	MemRegion * next;
	MemRegion * prev;
};


extern MemRegion * freeMemRegions; /* Points to the first free region, order is important here */
extern MemRegion * usedMemRegions; /* Points to the last allocated region */

extern MemRegion * sentinelRegion;


#define LOCK_LISTS                              \
    while (atomic_flag_test_and_set(&listLock)) \
		pause();

#define UNLOCK_LISTS \
    atomic_flag_clear(&listLock);


extern atomic_flag listLock;


#endif /* ! _XSTDMALLOC_FREE_LIST_H_ */
