#ifndef _XIPHOS_MEM_MAP_H_
#define _XIPHOS_MEM_MAP_H_


#include <attrs.h>
#include <types.h>


#define MMAP_RAM              0
#define MMAP_ACPI_TABLES      1
#define MMAP_ACPI_NVS         2
#define MMAP_NON_VOLATILE     3
#define MMAP_KERNEL           4	
#define MMAP_MEMORY_MAP	      0x50414D4D


typedef struct __PACKED__ {
	U32  type;
	PTR  base;
	U64  sz;
} MemRecord;


extern MemRecord * xiphosMemMap;


#endif /* ! _XIPHOS_MEM_MAP_H_ */
