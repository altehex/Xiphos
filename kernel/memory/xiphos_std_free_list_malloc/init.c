#include <memory/init.h>


#include "free_list.h"

#include <memory/mem_map.h>


/* FIXME: Make it more tidy and less hacky */
void
memory_init(const PTR memBase)
{
	MemRecord *        memRecord;
	PTR                memMapEnd;
	xsmfl_MemRegion *  memRegion;
	xsmfl_MemRegion *  prevRegion;
	
	/* Reserve one memory region for kernel, its stack and the low memory data */
	/* We need at least one memory region for allocation */
	xsmfl_usedMemRegions = (xsmfl_MemRegion *) memBase;
	
	xsmfl_usedMemRegions->sz   = (U64) memBase;
	xsmfl_usedMemRegions->next = &xsmfl_sentinelRegion;
	xsmfl_usedMemRegions->prev = &xsmfl_sentinelRegion;
	
    /* Parse memory map to get free regions */

	    /* gcc doesn't let me do things much simpler, otherwise it emits utter nonsense */
	xsmfl_freeMemRegions = (xsmfl_MemRegion *) ((PTR) xsmfl_usedMemRegions + sizeof(xsmfl_MemRegion));

	for (memRecord = (MemRecord *) ((PTR) xiphosMemMap + sizeof(MemRecord));
	     (U64) memRecord->base + memRecord->sz <= (U64) xsmfl_freeMemRegions;
		 memRecord = (MemRecord *) ((PTR) memRecord + sizeof(MemRecord))); // i'm dang serious, it doesn't have to look this ugly
	
	while (memRecord->type)  /* MMAP_RAM = 0 */
		memRecord = (MemRecord *) ((PTR) memRecord + sizeof(MemRecord));
	
	if (memRecord->base <= (PTR) xsmfl_freeMemRegions) {
		memRecord->base = (PTR) xsmfl_freeMemRegions;
		memRecord->sz   = (U64) memRecord->base + memRecord->sz - (U64) xsmfl_freeMemRegions;
	}
	else
		xsmfl_freeMemRegions = (xsmfl_MemRegion *) memRecord->base;

	memRegion = xsmfl_freeMemRegions;
	memRegion->sz   = memRecord->sz;
	    /* FIXME: It's a workaround so nothing changes inside xsmfl_sentinelRegion.
		 * The thing is gcc consider xsmfl_sentinelRegion relative address as an absolute address
		 * (if its offset is OFFSET, the address is OFFSET and not IMG_BASE + OFFSET for some reason)
		 * It's a linking problem and I can't weap my head around it at the moment. */
	memRegion->prev = &xsmfl_sentinelRegion;
	
	memMapEnd  = (PTR) xiphosMemMap + xiphosMemMap->sz;
	for (memRecord = (MemRecord *) ((PTR) memRecord + sizeof(MemRecord));
		 (PTR) memRecord != memMapEnd;
		 memRecord = (MemRecord *) ((PTR) memRecord + sizeof(MemRecord)))
	{
		if (memRecord->type) continue;  /* MMAP_RAM = 0 */

		prevRegion = memRegion;
		memRegion = (xsmfl_MemRegion *) memRecord->base;
		
		memRegion->sz    = memRecord->sz;
		memRegion->prev  = prevRegion;
		prevRegion->next = memRegion;
	}
	memRegion->next = &xsmfl_sentinelRegion;
}
