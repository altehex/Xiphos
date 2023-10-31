#ifndef _XIPHOS_MEM_MAP_H_
#define _XIPHOS_MEM_MAP_H_


#include <attrs.h>
#include <types.h>


#define ACPI_TABLES_RECORD_INDEX    1

#define __RAM              0
#define __ACPI_TABLES      1
#define __ACPI_NVS         2
#define __NON_VOLATILE     3
#define __KERNEL           4	
#define __MEMORY_MAP	   0x0D1E0D1E


typedef struct __PACKED__ {
	U32     type;
	void *  base;
	U64     sz;
} MemRecord;


static __UNUSED__
MemRecord * xiphosMemMap = 0x0000000000000000;
	

#endif /* ! _XIPHOS_MEM_MAP_H_ */
