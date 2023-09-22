#ifndef _ELF_H_
#define _ELF_H_

#include <types.h>


#define DT_NULL     0

#define DT_RELA     7
#define DT_RELASZ   8
#define DT_RELAENT  9

#define ELF64_R_TYPE(i)     ((i) & 0xffffffff)

#define R_X86_64_NONE       0
#define R_X86_64_RELATIVE   8

typedef U64     Elf64Addr;
typedef I64     Elf64Sxword;
typedef U64     Elf64Xword;

typedef struct {
	Elf64Sxword  dTag;
	union {
		Elf64Xword  dVal;
		Elf64Addr   dPtr;
	} dUn;
} Elf64Dyn;

typedef struct {
	Elf64Addr   rOffset;
	Elf64Xword  rInfo;
} Elf64Rel;


#endif /* !_ELF_H_ */
