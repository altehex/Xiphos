#ifndef _STDLIB_H_
#define _STDLIB_H_


#include <include/attrs.h>
#include <include/types.h>


                                 PTR __calloc(U64, SIZE64);
__HOT__ __WEAK__ __MALLOC_LIKE__ PTR __malloc(SIZE64);
__HOT__ __WEAK__                 void __free(PTR);


#define calloc(_1, _2)  __calloc(_1, _2)
#define free(_1)        __free(_1)
#define malloc(_1)      __malloc(_1)


#endif /* ! _STDLIB_H_ */
