#ifndef _TYPES_H_
#define _TYPES_H_

/* Fixed-size types */
typedef unsigned char           U8;
typedef unsigned short int      U16;
typedef unsigned int            U32;

typedef signed char             I8;
typedef signed short int        I16;
typedef signed int              I32;

#if __WORDSIZE == 64
typedef unsigned long int       U64;
typedef signed long int         I64;
#else
typedef unsigned long long int  U64;
typedef signed long long int    I64;
#endif 

#endif /* !_TYPES_H_ */
