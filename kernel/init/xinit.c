#include <acpi.h>
#include <attrs.h>
#include <types.h>
#include <mp.h>

#include <sched/idle.h>

#include <devman/acpi.h>

#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
#   include <setup_console.h>
#endif


__NORETURN__ __XINIT__(xiphos_init) void
xiphos_init(AcpiXsdp * xsdp, U64 coreNum)
{
	Core * xiphosCores; /* Global core array */

	xiphosCores = enumerate_cores(coreNum);
	
#if !defined CONFIG_NO_LOGS_AT_STARTUP || CONFIG_HEADLESS
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
	 *     - Emuman (if en
	 abled)
	 * - Starting services
	 */

	/* xiphos_idle(); */

	while (1) {}
}
