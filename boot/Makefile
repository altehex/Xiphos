# Address table

EFI_DIR  := $(SRC_ROOT)/build/efi
BOOT_DIR := $(EFI_DIR)/boot
IMG_DIR  := $(EFI_DIR)/xiphos

# For EFI_FILE_PROTOCOL.Open()
IMG_PATH = \"\\efi\\xiphos\\$(PACKAGE_NAME).img\"
IMG_SIZE = $(shell stat -L -c %s $(IMG_DIR)/$(PACKAGE_NAME).img)

export STACK_SIZE = 1024

export FASM_DEFINES = -dFRAMEBUFFER=$(FRAMEBUFFER) \
					  -dIMG_BASE=$(IMG_BASE) \
					  -dIMG_BASE_QUOTED=\"$(IMG_BASE)\" \
					  -dIMG_NAME=\"$(PACKAGE_NAME)\" \
					  -dIMG_PATH=$(IMG_PATH) \
					  -dIMG_SIZE=$(IMG_SIZE) \
					  -dMEM_MAP_BASE=$(MEM_MAP_BASE) \
					  -dRSDP=$(RSDP) \
					  -dSTACK_SIZE=$(STACK_SIZE) 

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
