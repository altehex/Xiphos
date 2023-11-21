#ifndef _STDLIB_H_
#define _STDLIB_H_


#include <include/attrs.h>
#include <include/types.h>


__HOT__ __WEAK__ __MALLOC_LIKE__ PTR _malloc(SIZE32);
__HOT__ __WEAK__ void _free(PTR);


#define free(_1)   _free(_1)
#define malloc(_1) _malloc(_1)


#endif /* ! _STDLIB_H_ */
