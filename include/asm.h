#ifndef _XIPHOS_ASM_H_
#define _XIPHOS_ASM_H_


#include <attrs.h>
#include <types.h>


/* Operand ordering is the same as in Intel syntax */

inline __ALWAYS_INLINE__ U8
in_byte(__IN__ U8 port)
{
	register U8 byte __asm__ ("al");
	
	__asm__ __volatile__
	(
	    "in      %[port], %0;"
    : "=r"(byte)
	: [port]"N"(port));

	return byte;
}

inline __ALWAYS_INLINE__ U16
in_word(__IN__ U8 port)
{
	register U16 word __asm__ ("ax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %0;"
    : "=r"(word)
	: [port]"N"(port));

	return word;
}

inline __ALWAYS_INLINE__ U32
in_dword(__IN__ U8 port)
{
	register U32 dword __asm__ ("eax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %0;"
    : "=r"(dword)
	: [port]"N"(port));

	return dword;
}

#define in(_1, _2)   _1 = _Generic((_1), \
								   U8:  in_byte,	\
								   U16: in_word,	\
								   U32: in_dword) (_2)

inline __ALWAYS_INLINE__ void
out_to_imm8_byte(__IN__ U8 port,
		         __IN__ U8 byte)
{
	register U8 __byte __asm__ ("al") = byte;
	
	__asm__ __volatile__
	(
	    "out     %[byte], %[port]"
    :
	: [port]"N"(port), [byte]"r"(__byte));
}

inline __ALWAYS_INLINE__ void
out_to_imm8_word(__IN__ U8  port,
		         __IN__ U16 word)
{
	register U16 __word __asm__ ("ax") = word;
		
	__asm__ __volatile__
	(
	    "out     %[word], %[port]"
    : 
	: [port]"N"(port), [word]"r"(__word));
}

inline __ALWAYS_INLINE__ void
out_to_imm8_dword(__IN__ U8  port,
		          __IN__ U32 dword)
{
	register U32 __dword __asm__ ("eax") = dword;
	
	__asm__ __volatile__
	(
	    "out     %[dword], %[port]"
    :
	: [port]"N"(port), [dword]"r"(__dword));
}

inline __ALWAYS_INLINE__ void
out_to_dx_byte(__IN__ U16 port,
		       __IN__ U8  byte)
{
	register U16 __port __asm__ ("dx") = port;
	register U8  __byte __asm__ ("al") = byte;
	
	__asm__ __volatile__
	(
	    "out     %[byte], %[port]"
    :
	: [port]"r"(__port), [byte]"r"(__byte));
}

inline __ALWAYS_INLINE__ void
out_to_dx_word(__IN__ U16 port,
		       __IN__ U16 word)
{
	register U16 __port __asm__ ("dx") = port;
	register U16 __word __asm__ ("ax") = word;
	
	__asm__ __volatile__
	(
	    "out     %[word], %[port]"
    : 
	: [port]"r"(__port), [word]"r"(__word));
}

inline __ALWAYS_INLINE__ void
out_to_dx_dword(__IN__ U16 port,
		        __IN__ U32 dword)
{
	register U16 __port __asm__ ("dx")   = port;
	register U32 __dword __asm__ ("eax") = dword;
	
	__asm__ __volatile__
	(
	    "out     %[dword], %[port]"
    :
	: [port]"r"(__port), [dword]"r"(__dword));
}

#define out_to_imm8(_1, _2)  _Generic((_2), \
							          U8:  out_to_imm8_byte, \
							          U16: out_to_imm8_word, \
							          U32: out_to_imm8_dword) (_1, _2)

#define out_to_dx(_1, _2)     _Generic((_2), \
							          U8:  out_to_dx_byte, \
							          U16: out_to_dx_word, \
							          U32: out_to_dx_dword) (_1, _2)

#define out(_1, _2)   _Generic((_1), \
							   U8:  _Generic((_2), \
							                 U8:  out_to_imm8_byte, \
							                 U16: out_to_imm8_word, \
							                 U32: out_to_imm8_dword), \
							   U16: _Generic((_2), \
							                 U8:  out_to_dx_byte, \
							                 U16: out_to_dx_word, \
							                 U32: out_to_dx_dword)) (_1, _2)

inline __ALWAYS_INLINE__ void
int1(void)
{
	__asm__ __volatile__
	( "int1;" );
}


#endif /* ! _XIPHOS_ASM_H_ */
