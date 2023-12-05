#ifndef _XIPHOS_TYPES_H_
#define _XIPHOS_TYPES_H_

/*
 *  Integer types.
 */

typedef unsigned char           U8;
typedef unsigned short int      U16;
typedef unsigned int            U32;
typedef unsigned long int       U64;

typedef signed char             I8;
typedef signed short int        I16;
typedef signed int              I32;
typedef signed long int         I64;

/* Universal pointer */
typedef void *                  PTR;
typedef U32                     PTR32;
typedef char *                  CHARPTR;

/* Universal function pointer */
typedef PTR (*FUNC)(PTR);

/*
 *  Types just for convenience
 */

typedef U8      CHAR8;
typedef U8      OFFSET8;

typedef U32     PORT32;
typedef U32     SIZE32;
typedef U64     SIZE64;

/*
 *  Macros
 */

#define MAX_U64  (U64) -1


#endif /* ! _XIPHOS_TYPES_H_ */
