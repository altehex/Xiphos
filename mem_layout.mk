export EFI_DIR  := $(SRC_ROOT)/build/efi
export BOOT_DIR := $(EFI_DIR)/boot
export IMG_DIR  := $(EFI_DIR)/xiphos

export IMG_BASE 		= 0x00100000
export SYS_DATA_BASE	= 0x00000000

# System data tables in order:
# - ACPI tables
# - Memory map
# - Paging tables
