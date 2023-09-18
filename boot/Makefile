.PHONY := bootloader
bootloader: firmware

.PHONY += firmware
firmware: uefi # bios

.PHONY += uefi
uefi:
	$(_ECHO)$(MAKE) -C $(SRC_ROOT)/firmware/uefi

.PHONY += bios
bios:

