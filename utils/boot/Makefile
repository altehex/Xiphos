# For EFI_FILE_PROTOCOL.Open()
IMG_PATH = \"\\efi\\xiphos\\$(PACKAGE_NAME).img\"

STACK_SIZE 		= 1024
IMG_SIZE  		= 

FASM_DEFINES = -dIMG_BASE=$(IMG_BASE) \
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

CLEAN = *.efi *.fas

.PHONY += clean
clean:
	$(RM) $(CLEAN)
