# It's right after the system reserved memory
# (for now. i'll make it higher half)
export IMG_BASE		= 0x00100000
export FRAMEBUFFER 	= 0xfffffffffc000000

# Don't fucking use it
export SYSTEM_RESERVED 		= 0x000A0000
export SYSTEM_RESERVED_END	= 0x000FFFFF

# Data tables (fetched at boot for the kernel to use)

export ACPI_TABLES_BASE		= 0x00000000
							# 0x00000007
export MEM_MAP_BASE			= 0x00000500
export PML4_BASE 			= 0x00000700
