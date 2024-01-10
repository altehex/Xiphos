#include "acpi.h"

#include <include/acpi.h>
#include <include/attrs.h>
#include <include/types.h>


void
acpi_init(__UNUSED__ AcpiXsdp * xsdp)
{
	return;
}


PTR
acpi_locate_table(CHARPTR sig, AcpiXsdt * xsdt)
{
	AcpiTableDesc * acpiTable;
	U32             currSig;
	U32             _sig;

	/* FIXME: Does it even work? */
	_sig = (U32) *sig;
	acpiTable = (AcpiTableDesc *) xsdt->entries;
	do {
	    currSig = (U32) *(acpiTable->sig);
		acpiTable += sizeof(U64);
	} while (_sig != currSig);
	
	return acpiTable;
}
