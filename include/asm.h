#ifndef _XIPHOS_ASM_H_
#define _XIPHOS_ASM_H_


#include <attrs.h>
#include <types.h>


/* To use with in() */
#define BYTE    (U8)  0xFF
#define WORD    (U16) 0xFFFF


/* Operand ordering is the same as in Intel syntax */

static inline U8
in_from_imm8_byte(U8 port)
{
	register U8 byte __asm__ ("al");
	
	__asm__ __volatile__
	(
	    "in      %[port], %[byte]"
    : [byte]"=r"(byte)
	: [port]"N"(port));

	return byte;
}

static inline U16
in_from_imm8_word(U8 port)
{
	register U16 word __asm__ ("ax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %[word]"
    : [word]"=r"(word)
	: [port]"N"(port));

	return word;
}

static inline U32
in_from_imm8_dword(U8 port)
{
	register U32 dword __asm__ ("eax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %[dword]"
    : [dword]"=r"(dword)
	: [port]"N"(port));

	return dword;
}

static inline U8
in_from_dx_byte(U16 port)
{
	register U16 __port __asm__ ("dx") = port;
	register U8 byte __asm__ ("al");
	
	__asm__ __volatile__
	(
	    "in      %[port], %[byte]"
    : [byte]"=r"(byte)
	: [port]"r"(__port));

	return byte;
}

static inline U16
in_from_dx_word(U16 port)
{
	register U16 __port __asm__ ("dx") = port;
	register U16 word __asm__ ("ax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %0"
    : [word]"=r"(word)
	: [port]"r"(__port));

	return word;
}

static inline U32
in_from_dx_dword(U16 port)
{
	register U16 __port __asm__ ("dx") = port;
	register U32 dword __asm__ ("eax");
	
	__asm__ __volatile__
	(
	    "in      %[port], %[dword]"
    : [dword]"=r"(dword)
	: [port]"r"(__port));

	return dword;
}

#define in(_1, _2)   _Generic((_2), \
		                      U8:  _Generic((_1), \
						                    U8:  in_from_imm8_byte,	\
					                        U16: in_from_imm8_word,	\
							                U32: in_from_imm8_dword), \
                              U16: _Generic((_1), \
											U8:  in_from_dx_byte, \
											U16: in_from_dx_word, \
											U32: in_from_dx_dword)) (_2)

static inline void
out_to_imm8_byte(U8 port,
		         U8 byte)
{
	register U8 __byte __asm__ ("al") = byte;
	
	__asm__ __volatile__
	(
	    "out     %[byte], %[port]"
    :
	: [port]"N"(port), [byte]"r"(__byte));
}

static inline void
out_to_imm8_word(U8  port,
		         U16 word)
{
	register U16 __word __asm__ ("ax") = word;
		
	__asm__ __volatile__
	(
	    "out     %[word], %[port]"
    : 
	: [port]"N"(port), [word]"r"(__word));
}

static inline void
out_to_imm8_dword(U8  port, U32 dword)
{
	register U32 __dword __asm__ ("eax") = dword;
	
	__asm__ __volatile__
	(
	    "out     %[dword], %[port]"
    :
	: [port]"N"(port), [dword]"r"(__dword));
}

static inline void
out_to_dx_byte(U16 port, U8  byte)
{
	register U16 __port __asm__ ("dx") = port;
	register U8  __byte __asm__ ("al") = byte;
	
	__asm__ __volatile__
	(
	    "out     %[byte], %[port]"
    :
	: [port]"r"(__port), [byte]"r"(__byte));
}

static inline void
out_to_dx_word(U16 port, U16 word)
{
	register U16 __port __asm__ ("dx") = port;
	register U16 __word __asm__ ("ax") = word;
	
	__asm__ __volatile__
	(
	    "out     %[word], %[port]"
    : 
	: [port]"r"(__port), [word]"r"(__word));
}

static inline void
out_to_dx_dword(U16 port, U32 dword)
{
	register U16 __port __asm__ ("dx")   = port;
	register U32 __dword __asm__ ("eax") = dword;
	
	__asm__ __volatile__
	(
	    "out     %[dword], %[port]"
    :
	: [port]"r"(__port), [dword]"r"(__dword));
}

#define out(_1, _2)   _Generic((_1), \
							   U8:  _Generic((_2), \
							                 U8:  out_to_imm8_byte, \
							                 U16: out_to_imm8_word, \
							                 U32: out_to_imm8_dword), \
							   U16: _Generic((_2), \
							                 U8:  out_to_dx_byte, \
							                 U16: out_to_dx_word, \
							                 U32: out_to_dx_dword)) (_1, _2)

static inline void
int1(void)
{
	__asm__ __volatile__
	( "int1;" );
}


#endif /* ! _XIPHOS_ASM_H_ */
