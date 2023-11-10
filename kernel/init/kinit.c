#include <attrs.h>

#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
#   include <setup_console.h>
#endif


void __NORETURN__ __KINIT__(kinit)
kinit(void)
{
#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
	api_setup_boot_stdout();
#endif
	
	while (1) {}
}
