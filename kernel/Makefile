KERNEL_IMAGE_DIR=$(SRC_ROOT)/build/efi/xiphos
LD_SCRIPT=$(SRC_ROOT)/kernel/kernel.lds

OBJ = kernel.o

.PHONY := xiphos
xiphos: $(PACKAGE_NAME).img
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(PACKAGE_NAME).img: $(OBJ)
	$(OBJCOPY) -O binary -j .text $^ $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

kernel.o: kernel.c

CLEAN = *.img *.o

.PHONY += clean
clean:
	$(_QUIET)$(RM) $(CLEAN)
