#include <mem_map.h>


#include <types.h>


/* Declared in include/mem_map.h */
U64 get_total_memory()
{
	MemRecord * lastMemRec;
	U64         totalMem;

	lastMemRec = (MemRecord *) ((U64) xiphosMemMap + xiphosMemMap->sz - sizeof(MemRecord));
	totalMem = (U64) lastMemRec->base + lastMemRec->sz;
	
	return totalMem;
}
