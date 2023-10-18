#ifndef _TYPES_H_
#define _TYPES_H_

/*
 * Integer types.
 */

/* Fixed-size types */
typedef unsigned char           U8;
typedef unsigned short int      U16;
typedef unsigned int            U32;
typedef unsigned long int       U64;

typedef signed char             I8;
typedef signed short int        I16;
typedef signed int              I32;

#ifdef __SIZEOF_INT128__
typedef unsigned __int128   U128;
typedef signed   __int128   I128;
#endif

#endif /* !_TYPES_H_ */
