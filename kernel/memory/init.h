#ifndef _XIPHOS_MEM_INIT_H_
#define _XIPHOS_MEM_INIT_H_


#include <attrs.h>
#include <types.h>

#include <memory/mem_map.h>


__XINIT__() __attribute__((nonnull (1))) void memory_init(const PTR);


#endif /* ! _XIPHOS_MEM_INIT_H_ */
