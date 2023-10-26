#include <acpi.h>

#include <mem_map.h>
#include <types.h>


void
acpi_init(MemRecord * mMap)
{	
	MemRecord * acpiRecord = &mMap[ACPI_TABLES_RECORD_INDEX];
	for (U64 offset = 0; offset < acpiRecord->sz; ) {
	}

	while (1) {}
	
}
