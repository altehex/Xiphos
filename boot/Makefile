# For EFI_FILE_PROTOCOL.Open()
IMG_PATH = \"\\efi\\xiphos\\$(PACKAGE_NAME).img\"

export STACK_SIZE 		= 1024
export IMG_SIZE  		= 

export FASM_DEFINES = -dIMG_BASE=$(IMG_BASE) \
					  -dIMG_BASE_QUOTED=\"$(IMG_BASE)\" \
					  -dIMG_NAME=\"$(PACKAGE_NAME)\" \
					  -dIMG_PATH=$(IMG_PATH) \
					  -dIMG_SIZE=$(IMG_SIZE) \
					  -dSTACK_SIZE=$(STACK_SIZE) \
					  -dSYS_DATA_BASE=$(SYS_DATA_BASE)

.PHONY := all
all: IMG_SIZE = $(shell stat -L -c %s $(IMG_DIR)/$(PACKAGE_NAME).img)
all: bootx64.efi

%.efi: %.asm
	$(FASM) $(FASM_DEFINES) $<
	$(MKDIR) -p $(BOOT_DIR)
	$(CP) $@ $(BOOT_DIR)

bootx64.efi: bootx64.asm

CLEAN = *.efi *.fas

clean:
	$(RM) $(CLEAN)

.PHONY += test
test:
		@echo	"* Kernel image base:    "$(IMG_BASE)
		@echo	"* Stack size(in bytes): "$(STACK_SIZE)
