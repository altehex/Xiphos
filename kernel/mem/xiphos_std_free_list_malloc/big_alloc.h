#ifndef _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_
#define _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_


#include "free_list.h"

#include <stddef.h>

#include <include/asm.h>
#include <include/mem.h>

#include <mem/mem_map.h>


static inline PTR
__big_alloc(SIZE64 sz)
{
	MemRegion *  targetRegion;  /* Target region */
	MemRegion *  freeRegion;    /* What is remained after region splitting/next free region */

	if (__UNLIKELY__(!sz))
		return NULLPTR;
		
	sz = (sz + 7) & 0xF8; /* Align */

	LOCK_LISTS;
	
	/* Find unlocked free region of a fitting size */
	for (targetRegion = freeMemRegions;
		 targetRegion->sz < sz;
		 targetRegion = targetRegion->prev)

	if (targetRegion == sentinelRegion) {
		UNLOCK_LISTS
		return NULLPTR;
	}
	
	/* Split the finded region if it's bigger than needed */
	if (__LIKELY__(sz != targetRegion->sz)) {
		freeRegion = (PTR) ((U64) targetRegion + sizeof(MemRegion) + sz);

		freeRegion->sz   = targetRegion->sz - sz - sizeof(MemRegion);
		freeRegion->prev = targetRegion->prev;
		freeRegion->next = targetRegion->next;

		targetRegion->sz = sz;
	}
	else
		freeRegion = targetRegion->next;

	if (targetRegion == freeMemRegions)
		freeMemRegions = freeRegion;
	
	/* Fix the order in free and used lists */
	targetRegion->prev->next = targetRegion->next;
	targetRegion->next->prev = targetRegion->prev;
	
	usedMemRegions->next = targetRegion;
	targetRegion->prev = usedMemRegions;
	targetRegion->next = sentinelRegion;

	usedMemRegions = targetRegion;
	
	UNLOCK_LISTS;
	
	return (PTR) targetRegion + sizeof(MemRegion);
}


static inline void
__big_free(PTR buf)
{
	MemRegion *  targetRegion;     /* The region to free */
	MemRegion *  nextNearbyRegion; /* The next nearby free region */
	MemRegion *  prevNearbyRegion; /* The previous nearby free region */

	if (__UNLIKELY__(!buf))
		return;

	LOCK_LISTS;
	
	targetRegion = buf - sizeof(MemRegion);
	
	/* Remove the region from the used list */
	targetRegion->prev->next = targetRegion->next;
	targetRegion->next->prev = targetRegion->prev;

	if (targetRegion == usedMemRegions)
		usedMemRegions = targetRegion->prev;
	
	/* Look for nearby free regions */
	for (nextNearbyRegion = freeMemRegions;
	     nextNearbyRegion < targetRegion;
		 nextNearbyRegion = nextNearbyRegion->next);
	
	prevNearbyRegion = nextNearbyRegion->prev;

	/* Merge nearby regions if they're adjacent */
	if ((prevNearbyRegion != sentinelRegion) &&
		((U64) prevNearbyRegion + prevNearbyRegion->sz + sizeof(MemRegion) == (U64) targetRegion))
	{
		prevNearbyRegion->sz += targetRegion->sz + sizeof(MemRegion);
		targetRegion = prevNearbyRegion;
	}
	else {
		prevNearbyRegion->next = targetRegion;
		targetRegion->prev = prevNearbyRegion;
	}

	if ((nextNearbyRegion != sentinelRegion) &&
		((U64) buf + ((MemRegion *) (buf - sizeof(MemRegion)))->sz == (U64) nextNearbyRegion))
	{
		nextNearbyRegion->next->prev = targetRegion;
		
		targetRegion->sz += nextNearbyRegion->sz + sizeof(MemRegion);
		targetRegion->next = nextNearbyRegion->next;
	}
	else if (targetRegion != prevNearbyRegion) {
		targetRegion->next = nextNearbyRegion;
		nextNearbyRegion->prev = targetRegion;
	}
	
	if (nextNearbyRegion == freeMemRegions)
		freeMemRegions = targetRegion;
	
	UNLOCK_LISTS;
}



#endif /* ! _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_ */
