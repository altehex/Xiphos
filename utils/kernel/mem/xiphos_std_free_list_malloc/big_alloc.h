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
	MemRegion * targetRegion; /* Target region */
	MemRegion * allocRegion;  /* Region to return */

	if (__UNLIKELY__(!sz))
		return NULLPTR;
	
	LOCK_LISTS;
		
	sz = (sz + 7) & 0xF8; /* Align */

	/* Find unlocked free region of a fitting size */
	for (targetRegion = freeMemRegions;
		 targetRegion->sz < sz;
		 targetRegion = targetRegion->prev)

	if (targetRegion == sentinelRegion)
		return NULLPTR;

	allocRegion = targetRegion;
	
	/* Divide the finded region if it's bigger than needed */
	if (__LIKELY__(sz != targetRegion->sz)) {
		targetRegion = (PTR) ((U64) allocRegion + sizeof(MemRegion) + sz);

		targetRegion->sz    = allocRegion->sz - sz;
		targetRegion->prev  = allocRegion->prev;
		targetRegion->next  = allocRegion->next;

		allocRegion->sz = sz;
	}
	else {
		targetRegion = targetRegion->next;
	}

	if (allocRegion == freeMemRegions)
		freeMemRegions = targetRegion;
	
	/* Fix the order in free and used lists */
	allocRegion->prev->next = allocRegion->next;
	allocRegion->next->prev = allocRegion->prev;
	
	usedMemRegions->next = allocRegion;
	allocRegion->prev = usedMemRegions;
	allocRegion->next = sentinelRegion;

	usedMemRegions = allocRegion;
	
	UNLOCK_LISTS;
	
	return (PTR) allocRegion + sizeof(MemRegion);
}


static inline void
__big_free(PTR buf)
{
	MemRegion * targetRegion;     /* The region to free */
	MemRegion * nextNearbyRegion; /* The next nearby free region */
	MemRegion * prevNearbyRegion; /* The previous nearby free region */

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
