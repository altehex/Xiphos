#ifndef _STDLIB_H_
#define _STDLIB_H_


#include <include/attrs.h>
#include <include/types.h>


                                 PTR _calloc(U64, SIZE64);
__HOT__ __WEAK__ __MALLOC_LIKE__ PTR _malloc(SIZE64);
__HOT__ __WEAK__                 void _free(PTR);


#define calloc(_1, _2)  _calloc(_1, _2)
#define free(_1)        _free(_1)
#define malloc(_1)      _malloc(_1)


#endif /* ! _STDLIB_H_ */
