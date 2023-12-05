#include <mem_map.h>


#include <types.h>


/* Declared in include/mem_map.h */
U64 get_total_memory()
{
	MemRecord * lastMemRec = (MemRecord *) ((U64) xiphosMemMap + xiphosMemMap->sz - sizeof(MemRecord));
	
	return (U64) lastMemRec->base + lastMemRec->sz;
}
