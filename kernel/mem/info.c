#include <mem_map.h>


#include <types.h>


U64 get_total_memory()
{
	volatile MemRecord * lastMemRec;
	U64                  totalMem;

	lastMemRec = (MemRecord *) ((U64) xiphosMemMap + xiphosMemMap->sz - sizeof(MemRecord));
	totalMem = (U64) lastMemRec->base + lastMemRec->sz;
	
	return totalMem;
}
