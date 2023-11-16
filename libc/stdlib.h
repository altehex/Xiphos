#ifndef _STDLIB_H_
#define _STDLIB_H_


#include <include/attrs.h>
#include <include/types.h>


__WEAK__ PTR _malloc(SIZE32);

#define malloc(_1) _malloc(_1)


#endif /* ! _STDLIB_H_ */
