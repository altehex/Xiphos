if ~ defined _MEM_MAP_INC_
define _MEM_MAP_INC_	1
	

include "../types.inc"
include "../macro.inc"

	
struc __memRecord {
	.type	I32
	.base	PTR
	.sz		I64
}

struc __memMap {
	 .sz	 I32
	 .map	 PTR
}

;; Memory types
__RAM			=	0	; <-- Everything else, except runtime regions and unusable memory
__ACPI_TABLES	= 	1	; <-- EfiACPIReclaimMemory
__ACPI_NVS		= 	2	; <-- EfiACPIMemoryNVS
__NON_VOLATILE  =   4   ; <-- EfiPersistentMemory

	
TABLE	\
		__memRecord,	\
		__memMap

	
end if 		; ~ defined _MEM_MAP_INC_
