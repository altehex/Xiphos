UEFI_DIR    = $(SRC_ROOT)/firmware/uefi
UEFI_LDS    = $(UEFI_DIR)/elf_efi.lds

UEFI_FORMAT = efi-app-x86_64

UEFI_CFLAGS = -ffreestanding \
			  -fno-stack-protector \
			  -fshort-wchar \
			  -fPIC \
			  -m64 \
	          -mno-red-zone
ifeq (0, $(CONFIG_LLVM))
UEFI_CFLAGS += -maccumulate-outgoing-args
endif

UEFI_LDFLAGS = -t -T $(UEFI_LDS) \
			   -Bsymbolic \
			   -shared \
			   -nostdlib \
			   -znocombreloc

export UEFI_CFLAGS

OBJCOPYFLAGS := -j .text \
			    -j .sdata \
			    -j .data \
			    -j .dynamic \
			    -j .dynsym \
			    -j .rel \
			    -j .rela \
			    -j .reloc \
			    -S --target=$(UEFI_FORMAT)

OBJ = $(UEFI_DIR)/*.o

.PHONY := all
all: $(if $(CONFIG_EFI), uefi bootx64.efi, boot.bin)
	$(CP) $(filter bootx64.efi boot.bin, $^) $(SRC_ROOT)/build

bootx64.efi: bootx64.so
	objcopy $(OBJCOPYFLAGS) $^ $@

bootx64.so: bootx64.o $(shell $(CC) -print-libgcc-file-name)
	$(LD) $(UEFI_LDFLAGS) $^ $(OBJ) -o $@

bootx64.o: bootx64.c
	$(CC) $(UEFI_CFLAGS) $(INCLUDE) -o bootx64.o -c bootx64.c

.PHONY += uefi
uefi:
	$(MAKE) -C $(UEFI_DIR)

boot.bin: # WIP


clean:
	$(RM) *.o

.PHONY += test
test:
		@echo	"* EFI flag: "$(CONFIG_EFI)
