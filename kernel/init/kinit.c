#include <mem_map.h>
#include <types.h>

#include <acpi.h>
#include <cpu.h>
#include <irq.h>


void __NORETURN__
kinit(void)
{
	 MemRecord * memMap;

	/* Copy memory map base */
	__asm__ __volatile__ (
	    "mov    %%rax, %0"
    : "=r"(memMap) : : );

	/* Copy CpuInfo */
	CpuInfo * cpuInfoOnBoot;
	__asm__ __volatile__ (
	    "mov    %%rbx, %0"					  
    : "=r"(cpuInfoOnBoot) : : );
	setup_cpuinfo(cpuInfoOnBoot);

	/* Set up interrupts */
	/* setup_irqs(); */

	while (1) {}
}
