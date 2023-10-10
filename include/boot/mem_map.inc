if ~ defined _MEM_MAP_INC_
define _MEM_MAP_INC_	1
	

include "../types.inc"
include "../macro.inc"

	
struc memHeader {
	.sz		I32
	.rec	PTR
}
	
struc memRecord {
	.type	I32
	.base	PTR
	.sz		I64
}

;; Memory types

__RESERVED		=	0	; <-- EfiRuntimeServicesCode, EfiRuntimeServicesData,
						;	  EfiLoaderCode, EfiLoaderData, EfiBootServicesCode,
						; 	  EfiBootServicesData, EfiReservedMemoryType
__RAM			=	1	; <-- EfiConventionalMemory
__ACPI_TABLES	= 	2	; <-- EfiACPIReclaimMemory
__ACPI_NVS		= 	3	; <-- EfiACPIMemoryNVS
__UNUSABLE		= 	4	; <-- EfiUnusableMemory
__NON_VOLATILE	= 	5	; <-- EfiPersistentMemory

	
TABLE memRecord, memHeader		

	
end if 		; ~ defined _MEM_MAP_INC_
