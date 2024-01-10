#include <mem/init.h>


#include "free_list.h"

#include <mem/mem_map.h>


void
alloc_init(PTR memBase)
{
	/* MemRecord * memRecord; */
	/* PTR         memMapEnd; */
	/* MemRegion * freeRegion; */
	/* MemRegion * prevRegion; */
	
	/* Reserve one MemRegion for kernel, its stack and the low memory data */
	/* We need at least one MemRegion for allocation */
	usedMemRegions = memBase;
	
	usedMemRegions->sz     = (U64) memBase;
	usedMemRegions->next   = sentinelRegion;
	usedMemRegions->prev   = sentinelRegion;

	freeMemRegions = usedMemRegions + sizeof(usedMemRegions);

	freeMemRegions->sz     = get_total_memory() - (U64) memBase - sizeof(MemRegion);
	freeMemRegions->next   = sentinelRegion;
	freeMemRegions->prev   = sentinelRegion;
	
	/* /\* Parse memory map *\/ (WIP) */ 
	/* for (memRecord = xiphosMemMap; */
	/*      memRecord->type; /\* MMAP_RAM = 0 *\/ */
	/* 	 memRecord += sizeof(MemRecord)); */

	/* freeRegion = memRecord->base; */
	/* memMapEnd  = xiphosMemMap + xiphosMemMap->sz; */
	/* prevRegion = sentinelRegion; */

	/* for (; */
	/* 	 memRecord != memMapEnd; */
	/* 	 memRecord += sizeof(MemRecord), freeRegion = memRecord->base) */
	/* 	if (memRecord->type == MMAP_RAM) { */
	/* 		freeRegion->sz   = memRecord->sz; */
	/* 		freeRegion->prev = prevRegion; */
	/* 		prevRegion->next = freeRegion; */

	/* 		prevRegion = freeRegion; */
	/* 	} */
	/* freeRegion->next = sentinelRegion; */
}
