#include <attrs.h>

#ifndef CONFIG_NO_LOGS_AT_STARTUP
#   include <api/console/xiphos_std_console/xiphos_std_console.h>
#endif


void __NORETURN__ __KINIT__(kinit)
kinit(void)
{
#ifndef CONFIG_NO_LOGS_AT_STARTUP
	setup_console();
#endif
	
	while (1) {}
}
