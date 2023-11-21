#ifndef _XIPHOS_ASM_H_
#define _XIPHOS_ASM_H_


#include <attrs.h>
#include <types.h>


#define BYTE    (U8) -1
#define WORD    (U16) -1

#define byte    U8
#define word    U16
#define dword   U32

/* Operand ordering is the same as in Intel syntax */

#define DECL_IN_FROM_IMM8(SIZE, A_REG)		 \
	static inline SIZE					     \
	in_from_imm8_##SIZE (U8 port)            \
	{                                        \
		register SIZE __in __asm__ (#A_REG); \
                                             \
		__asm__                              \
		(                                    \
			"in      %[port], %[in]"         \
		: [in]"=r"(__in)                     \
		: [port]"N"(port));                  \
                                             \
		return __in;                         \
	}

DECL_IN_FROM_IMM8(byte,  al)
DECL_IN_FROM_IMM8(word,  ax)
DECL_IN_FROM_IMM8(dword, eax)

#define DECL_IN_FROM_DX(SIZE, A_REG)               \
	static inline SIZE                             \
	in_from_dx_##SIZE(U16 port)                    \
	{                                              \
		register U16 __port __asm__ ("dx") = port; \
		register SIZE __in __asm__ (#A_REG);       \
                                                   \
		__asm__                                    \
		(                                          \
			"in      %[port], %[in]"               \
		: [in]"=r"(__in)                           \
		: [port]"r"(__port));                      \
                                                   \
		return __in;                               \
	}                                              

DECL_IN_FROM_DX(byte,  al)
DECL_IN_FROM_DX(word,  ax)
DECL_IN_FROM_DX(dword, eax)

#define DECL_OUT_TO_IMM8(SIZE, A_REG)               \
	static inline void                              \
	out_to_imm8_##SIZE(U8 port, SIZE out)           \
	{                                               \
		register SIZE __out __asm__ (#A_REG) = out; \
                                                    \
		__asm__                                     \
		(                                           \
			"out     %[out], %[port]"               \
		:                                           \
		: [port]"N"(port), [out]"r"(__out));        \
	}

DECL_OUT_TO_IMM8(byte,  al)
DECL_OUT_TO_IMM8(word,  ax)
DECL_OUT_TO_IMM8(dword, eax)

#define DECL_OUT_TO_DX(SIZE, A_REG)                   \
	static inline void                                \
	out_to_dx_##SIZE(U16 port, SIZE out)              \
	{                                                 \
		register U16   __port __asm__ ("dx")  = port; \
		register SIZE  __out __asm__ (#A_REG) = out;  \
                                                      \
		__asm__                                       \
		(                                             \
			"out     %[out], %[port]"                 \
		:                                             \
		: [port]"r"(__port), [out]"r"(__out));        \
	}

DECL_OUT_TO_DX(byte,  al)
DECL_OUT_TO_DX(word,  ax)
DECL_OUT_TO_DX(dword, eax)

#undef byte
#undef word
#undef dword

#define in(_1, _2)   _Generic((_2), \
		                      U8:  _Generic((_1), \
						                    U8:  in_from_imm8_byte,	\
					                        U16: in_from_imm8_word,	\
							                U32: in_from_imm8_dword), \
                              U16: _Generic((_1), \
											U8:  in_from_dx_byte, \
											U16: in_from_dx_word, \
											U32: in_from_dx_dword)) (_2)

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
