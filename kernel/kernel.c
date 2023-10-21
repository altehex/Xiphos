#include <mem_map.h>
#include <types.h>

#include <acpi.h>


void __NORETURN__
__start(void)
{
	 MemRecord * memMap;
	
	__asm__ __volatile__ (
	    "mov    %%rax, %0"
    : "=r"(memMap) : : "memory");

	
	while (1) {
	
	acpi_init(memMap); }
}
