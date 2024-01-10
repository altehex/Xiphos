
#include "config.h"

#include <devman/acpi.h>
#include <include/types.h>


__UNUSED__ void *
xstdpcie_get_table(AcpiXsdt * xsdt)
{
	return acpi_locate_table(ACPI_MCFG, xsdt);
}
