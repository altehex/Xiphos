#ifndef _XIPHOS_MEM_MAP_H_
#define _XIPHOS_MEM_MAP_H_


#include <attrs.h>
#include <types.h>


#define ACPI_TABLES_RECORD_INDEX    1

#define MMAP_RAM              0
#define MMAP_ACPI_TABLES      1
#define MMAP_ACPI_NVS         2
#define MMAP_NON_VOLATILE     3
#define MMAP_KERNEL           4	
#define MMAP_MEMORY_MAP	      0x50414D4D


typedef struct __PACKED__ {
	U32     type;
	void *  base;
	U64     sz;
} MemRecord;


/* NOTE: GCC emits ud2 without __USED__ attribute */
static __USED__ MemRecord * xiphosMemMap = 0x0000000000000000;


U64 get_total_memory(void);


#endif /* ! _XIPHOS_MEM_MAP_H_ */
