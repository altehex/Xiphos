export UEFI_CFLAGS = -ffreestanding         \
					 -fshort-wchar          \
			         -mno-red-zone          

export UEFI_LDFLAGS = -nostdlib             \
					  -Wl,-

.PHONY := bootloader
bootloader: bootx64.efi boot.bin

bootx64.efi: bootx64.o
# make bootx64.efi

bootx64.o: uefi
	$(CC) $(CFLAGS) $(UEFI_CFLAGS) $(INCLUDE) -o bootx64.o -c bootx64.c
#	$(LD) $(LDFLAGS) $(UEFI_LDFLAGS)

uefi: # uefi.o
	$(MAKE) -C $(SRC_ROOT)/firmware/uefi

boot.bin: # WIP

.PHONY += clean
clean:
	$(RM) *.o
