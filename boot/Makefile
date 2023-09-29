EFI_DIR := $(SRC_ROOT)/build/efi/boot

.PHONY := all
all: $(if $(CONFIG_EFI), bootx64.efi, boot.bin)

%.efi: %.asm
	$(FASM) $<
	$(MKDIR) -p $(EFI_DIR)
	$(CP) $@ $(EFI_DIR)

boot.bin: # WIP

CLEAN = *.efi *.fas

clean:
	$(RM) $(CLEAN)

.PHONY += test
test:
		@echo	"* EFI flag: "$(CONFIG_EFI)
