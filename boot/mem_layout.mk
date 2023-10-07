STACK_SIZE = 1024

# It's right after the system reserved memory
IMG_BASE	= 0x00100000

# Don't fucking use it
SYSTEM_RESERVED 	= 0x000A0000
SYSTEM_RESERVED_END	= 0x000FFFFF

# Data tables (fetched at boot for the kernel to use)
