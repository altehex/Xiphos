#include <mem_map.h>
#include <types.h>

#include <acpi.h>
#include <irq.h>

#ifndef CONFIG_HEADLESS
#   include <api/video/xiphos_std_vesa_api/setup_vesa.h>
#endif


void __NORETURN__ __KINIT__(kinit)
kinit(void)
{
#ifndef CONFIG_HEADLESS
	setup_vesa();
#endif
	
	while (1) {}
}
