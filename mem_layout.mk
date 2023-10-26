export EFI_DIR  := $(SRC_ROOT)/build/efi
export BOOT_DIR := $(EFI_DIR)/boot
export IMG_DIR  := $(EFI_DIR)/xiphos

# First 1 MB is reserved for system data(see below)
export SYS_DATA_BASE	= 0x00000000
export IMG_BASE 		= 0x00100000

# System data tables in order:
# - ACPI tables
# - Memory map
# - IDT
# - Paging tables
