#include <mem/init.h>

#include "free_list.h"

#include <mem_map.h>


void
alloc_init(PTR memBase)
{
	/* Reserve one MemRegion for kernel, its stack and the low memory data */
	usedMemRegions = memBase;
	
	usedMemRegions->canary = 0;
	usedMemRegions->flags  = 0;
	usedMemRegions->sz     = (U64) memBase + sizeof(MemRegion);
	usedMemRegions->next   = sentinelRegion;
	usedMemRegions->prev   = sentinelRegion;

	freeMemRegions = (MemRegion *) usedMemRegions->sz;

	freeMemRegions->canary = 0;
	freeMemRegions->flags  = 0;
	freeMemRegions->sz     = get_total_memory() - (U64) freeMemRegions;
	freeMemRegions->next   = sentinelRegion;
	freeMemRegions->prev   = sentinelRegion;
}
