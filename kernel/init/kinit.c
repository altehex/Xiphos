#include <attrs.h>

#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
#   include <setup_video.h>
#   include <setup_console.h>
#endif


void __NORETURN__ __KINIT__(kinit)
kinit(void)
{
#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
	libos_setup_video();
	api_setup_console();
#endif
	
	while (1) {}
}
