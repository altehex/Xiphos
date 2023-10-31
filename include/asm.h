#ifndef _XIPHOS_ASM_
#define _XIPHOS_ASM_


#include <attrs.h>
#include <types.h>


/* Operand ordering is the same as in Intel symtax */

inline __ALWAYS_INLINE__ void
out_byte(U8 port, U8 byte)
{
	__asm__ __volatile__
	(
	    "mov     %[byte], %%al;"
	    "out     %%al, %[port]"
    : : [port]"N"(port), [byte]"r"(byte) : "%al" );
}

inline __ALWAYS_INLINE__ void
out_word(U8 port, U16 word)
{
	__asm__ __volatile__
	(
	    "mov     %[word], %%ax;"
	    "out     %%ax, %[port]"
    : : [port]"N"(port), [word]"r"(word) : "%ax" );
}

inline __ALWAYS_INLINE__ void
out_dword(U8 port, U32 dword)
{
	__asm__ __volatile__
	(
	    "mov     %[dword], %%eax;"
	    "out     %%eax, %[port]"
    : : [port]"N"(port), [dword]"r"(dword) : "%eax" );
}

#define out(_1, _2)   _Generic((_2), \
							   U8:  out_byte, \
							   U16: out_word, \
							   U32: out_dword) (_1, _2)
	

#endif /* ! _XIPHOS_ASM_ */
