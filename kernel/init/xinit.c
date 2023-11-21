#include <acpi.h>
#include <attrs.h>
#include <types.h>
#include <mp.h>
#include <settings.h>

#include <mem/init.h>
#include <sched/idle.h>

/* #include <devman/init.h> */
/* #include <netman/init.h> */
/* #include <secman/init.h> */
/* #include <shaman/init.h> */

#if !defined DISPLAY_OFF
#   include <setup_console.h>
#endif


__NORETURN__ __XINIT__(xiphos_init) void
xiphos_init(PTR kernelStackBase, U64 coreNum)
{
	alloc_init(kernelStackBase);    /* Allocator initialization. */
	enumerate_cores(coreNum);     /* Create Core structures */
	
#if !defined DISPLAY_OFF
	setup_boot_stdout();
#endif

	/* xiphos_serve_on_all_cores(); */
	
	/* Things kernel should do at startup (the order might be different):
	 *------------------------------------------------*
	 * - (just for logging) VGA text mode stdout setup.
	 * - Arch-specific configuration (x86-64 only yet)
	 * - System initialization:
	 *     - SMP setup
	 *     - Scheduler setup
	 *     - Memory manager setup
	 *     - Interrupts setup
	 *     - ...
	 * - Subsystem initialization:
	 *     - Devman
	 *     - Netman
	 *     - Secman
	 *     - Shaman
	 *     - Emuman (if enabled)
	 * - Starting services
	 */

	/* xiphos_idle(); */

	while (1) {}
}
