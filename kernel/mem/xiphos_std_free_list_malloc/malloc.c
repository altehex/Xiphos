#include <stdlib.h>

#include "free_list.h"

#include <include/mem.h>
#include <include/types.h>


/*
 *  Standard allocator for Xiphos
 *--------------------------------------------*
 *  Returns NULLPTR if size is 0
 */
PTR
_malloc(SIZE32 size)
{
	if (__UNLIKELY__(size == 0))
		return NULLPTR;

	/* placeholder */
	return (PTR) 0xBABEBABE;
}
