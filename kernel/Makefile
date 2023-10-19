KERNEL_IMAGE_DIR=$(SRC_ROOT)/build/efi/xiphos
LD_SCRIPT=$(SRC_ROOT)/kernel/kernel.lds

OBJ = kernel.o
LDS = kernel.lds

.PHONY := xiphos
xiphos: $(PACKAGE_NAME).img
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(PACKAGE_NAME).img: $(OBJ)
	$(LD) $(LDFLAGS) -T $(LDS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

kernel.o: kernel.c

CLEAN = *.img *.o

.PHONY += clean
clean:
	$(_QUIET)$(RM) $(CLEAN)
