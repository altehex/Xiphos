#ifndef _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_
#define _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_


#include "free_list.h"

#include <stddef.h>

#include <include/asm.h>
#include <include/mem.h>


static inline PTR
__big_alloc(SIZE64 sz)
{
	xsmfl_MemRegion *  targetRegion;  /* Target region */
	xsmfl_MemRegion *  freeRegion;    /* What is remained after region splitting/Next free region */

	if (__UNLIKELY__(!sz))
		return NULLPTR;
		
	sz = (sz + 7) & 0xF8; /* Align */

	XSMFL_LOCK_LISTS;
	
	/* Find unlocked free region of a fitting size */
	for (targetRegion = xsmfl_freeMemRegions;
		 targetRegion->sz < sz;
		 targetRegion = targetRegion->prev)

	if (targetRegion == &xsmfl_sentinelRegion) {
		/* XSMFL_UNLOCK_LISTS */
		return NULLPTR;
	}
	
	/* Split the finded region if it's bigger than needed */
	if (__LIKELY__(sz != targetRegion->sz)) {
		freeRegion = (PTR) ((U64) targetRegion + sizeof(xsmfl_MemRegion) + sz);

		freeRegion->sz   = targetRegion->sz - sz - sizeof(xsmfl_MemRegion);
		freeRegion->prev = targetRegion->prev;
		freeRegion->next = targetRegion->next;

		targetRegion->sz = sz;
	}
	else
		freeRegion = targetRegion->next;

	if (targetRegion == xsmfl_freeMemRegions)
		xsmfl_freeMemRegions = freeRegion;
	
	/* Fix the order in free and used lists */
	targetRegion->prev->next = targetRegion->next;
	targetRegion->next->prev = targetRegion->prev;
	
	xsmfl_usedMemRegions->next = targetRegion;
	targetRegion->prev = xsmfl_usedMemRegions;
	targetRegion->next = &xsmfl_sentinelRegion;

	xsmfl_usedMemRegions = targetRegion;
	
	XSMFL_UNLOCK_LISTS;
	
	return (PTR) targetRegion + sizeof(xsmfl_MemRegion);
}


static inline void
__big_free(PTR buf)
{
	xsmfl_MemRegion *  targetRegion;     /* The region to free */
	xsmfl_MemRegion *  nextNearbyRegion; /* The next nearby free region */
	xsmfl_MemRegion *  prevNearbyRegion; /* The previous nearby free region */

	if (__UNLIKELY__(!buf))
		return;

	XSMFL_LOCK_LISTS;
	
	targetRegion = buf - sizeof(xsmfl_MemRegion);
	
	/* Remove the region from the used list */
	targetRegion->prev->next = targetRegion->next;
	targetRegion->next->prev = targetRegion->prev;

	if (targetRegion == xsmfl_usedMemRegions)
		xsmfl_usedMemRegions = targetRegion->prev;
	
	/* Look for nearby free regions */
	for (nextNearbyRegion = xsmfl_freeMemRegions;
	     nextNearbyRegion < targetRegion;
		 nextNearbyRegion = nextNearbyRegion->next);
	
	prevNearbyRegion = nextNearbyRegion->prev;

	/* Merge nearby regions if they're adjacent */
	if ((prevNearbyRegion != &xsmfl_sentinelRegion) &&
		((U64) prevNearbyRegion + prevNearbyRegion->sz + sizeof(xsmfl_MemRegion) == (U64) targetRegion))
	{
		prevNearbyRegion->sz += targetRegion->sz + sizeof(xsmfl_MemRegion);
		targetRegion = prevNearbyRegion;
	}
	else {
		prevNearbyRegion->next = targetRegion;
		targetRegion->prev = prevNearbyRegion;
	}

	if ((nextNearbyRegion != &xsmfl_sentinelRegion) &&
		((U64) buf + ((xsmfl_MemRegion *) (buf - sizeof(xsmfl_MemRegion)))->sz == (U64) nextNearbyRegion))
	{
		nextNearbyRegion->next->prev = targetRegion;
		
		targetRegion->sz += nextNearbyRegion->sz + sizeof(xsmfl_MemRegion);
		targetRegion->next = nextNearbyRegion->next;
	}
	else if (targetRegion != prevNearbyRegion) {
		targetRegion->next = nextNearbyRegion;
		nextNearbyRegion->prev = targetRegion;
	}
	
	if (nextNearbyRegion == xsmfl_freeMemRegions)
		xsmfl_freeMemRegions = targetRegion;
	
	XSMFL_UNLOCK_LISTS;
}



#endif /* ! _XSTDMALLOC_FREE_LIST_BIG_ALLOC_H_ */
