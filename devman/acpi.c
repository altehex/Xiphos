#include "acpi.h"

#include <include/acpi.h>
#include <include/types.h>


void
acpi_init(AcpiXsdp * xsdp)
{
	return;
}


PTR
acpi_locate_table(U32 sig, AcpiXsdt * xsdt)
{
	AcpiTableDesc * acpiTable;
	U32             currSig;

	for (acpiTable = (AcpiTableDesc *) xsdt->entries; sig != currSig; acpiTable += sizeof(U64))
		currSig = (U32) *(acpiTable->sig);
	
	return acpiTable;
}
