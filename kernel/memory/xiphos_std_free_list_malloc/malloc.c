#include <stdlib.h>


#include "big_alloc.h"
#include "free_list.h"

#include <include/asm.h>
#include <include/mem.h>
#include <include/types.h>


__UNUSED__ PTR __small_alloc();


/*
 *  Standard free list allocator for Xiphos
 *--------------------------------------------*
 *  Returns NULLPTR if size is 0
 */
PTR
_malloc(SIZE64 sz)
{
	if (__UNLIKELY__(sz == 0))
		return NULLPTR;

	if (sz <= XSMFL_BIG_ALLOC_THRESHOLD)
        /* return small_alloc(); */
		
	return __big_alloc(sz);
}


PTR _calloc(U64 num, SIZE64 sz)
{
	PTR buf;

	buf = _malloc(sz * num);
	__qfill(buf, sz * num, 0);

    return buf;
}


void
_free(PTR buf)
{
	/* NOTE: No options for small allocation yet */
	__big_free(buf);
}


PTR
__small_alloc()
{
	/* WIP */
	return NULLPTR;
}
