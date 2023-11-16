
#include "config.h"

#include <include/acpi.h>
#include <include/types.h>


void *
xstdpcie_get_table(AcpiXsdt * xsdt)
{
	return acpi_locate_table(ACPI_MCFG, xsdt);
}
