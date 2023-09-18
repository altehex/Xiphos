.PHONY := bootloader
bootloader: firmware

.PHONY += firmware
firmware: uefi # bios

.PHONY += uefi
uefi:
	$(_QUIET)$(MAKE) -C $(SRC_ROOT)/firmware/uefi

.PHONY += bios
bios:

.PHONY += clean
clean:
	@$(RM) *.o
