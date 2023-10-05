# Address table
include	mem_layout.mk

EFI_DIR  := $(SRC_ROOT)/build/efi
BOOT_DIR := $(EFI_DIR)/boot
IMG_DIR  := $(EFI_DIR)/thanatos

# For EFI_FILE_PROTOCOL.Open()
IMG_PATH = \"\\efi\\thanatos\\$(PACKAGE_NAME).img\"
IMG_SIZE = $(shell stat -L -c %s $(IMG_DIR)/$(PACKAGE_NAME).img)

export FASM_DEFINES = -dIMG_BASE=$(IMG_BASE) \
					  -dIMG_BASE_QUOTED=\"$(IMG_BASE)\" \
					  -dSTACK_SIZE=$(STACK_SIZE) \
					  -dIMG_NAME=\"$(PACKAGE_NAME)\" \
					  -dIMG_PATH=$(IMG_PATH) \
					  -dIMG_SIZE=$(IMG_SIZE)

.PHONY := all
all: $(if $(CONFIG_EFI), bootx64.efi, boot.bin)

%.efi: %.asm
	$(FASM) $(FASM_DEFINES) $<
	$(MKDIR) -p $(BOOT_DIR)
	$(CP) $@ $(BOOT_DIR)

boot.bin: # WIP

CLEAN = *.efi *.fas

clean:
	$(RM) $(CLEAN)

.PHONY += test
test:
		@echo	"* Image base:           "$(IMG_BASE)
		@echo	"* Stack size(in bytes): "$(STACK_SIZE)
		@echo	"* EFI flag:             "$(CONFIG_EFI)
