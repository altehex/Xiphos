#include <mem_map.h>
#include <types.h>

__memRecord * __acpiRecord;

int
__start(void)
{
	 __memRecord * __memMap;
	
	__asm__ __volatile__ (
	    "mov    %%rax, %0"
    : "=r"(__memMap) : : "memory");

	__acpiRecord = &__memMap[ACPI_TABLES_RECORD_INDEX];
	
	
	while (1) { }
}
