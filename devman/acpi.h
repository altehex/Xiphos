#ifndef _XDEVMAN_ACPI_H_
#define _XDEVMAN_ACPI_H_


#include "attrs.h"

#include <include/acpi.h>
#include <include/attrs.h>
#include <include/types.h>


__XINIT__() void acpi_init(AcpiXsdp *);
__DEVMAN__ PTR acpi_locate_table(__NONSTRING__ CHARPTR, AcpiXsdt *);


#endif /* ! _XDEVMAN_ACPI_H_ */
