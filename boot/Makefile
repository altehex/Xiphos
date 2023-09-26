.PHONY := all
all: $(if $(CONFIG_EFI), bootx64.efi, boot.bin)

%.efi: %.asm
	$(FASM) $<
	$(CP) $@ $(SRC_ROOT)/build/

boot.bin: # WIP

CLEAN = *.efi *.fas

clean:
	$(RM) $(CLEAN)

.PHONY += test
test:
		@echo	"* EFI flag: "$(CONFIG_EFI)
