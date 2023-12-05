#ifndef _XIPHOS_MEM_INIT_H_
#define _XIPHOS_MEM_INIT_H_


#include <attrs.h>
#include <types.h>

#include <mem/mem_map.h>


__XINIT_MEM__ __attribute__((nonnull (1))) __WEAK__ void alloc_init(PTR);


static inline void
memory_init(PTR memBase)
{
	xiphosTotalMemory = get_total_memory();
	alloc_init(memBase);
}


#endif /* ! _XIPHOS_MEM_INIT_H_ */
