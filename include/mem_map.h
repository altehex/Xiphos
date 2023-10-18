#ifndef _MEM_MAP_H_
#define _MEM_MAP_H_


#include <types.h>


#define __RAM              0
#define __ACPI_TABLES      1
#define __ACPI_NVS         2
#define __NON_VOLATILE     3
#define __KERNEL           4	
#define __MEMORY_MAP	   5  


typedef struct {
	U32     type;
	void *  base;
	U64     sz;
} __memRecord;

	

#endif /* ! _MEM_MAP_H_ */
