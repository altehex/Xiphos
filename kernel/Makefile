KERNEL_IMAGE_DIR=$(SRC_ROOT)/build/efi/xiphos
LD_SCRIPT=$(SRC_ROOT)/kernel/kernel.lds

KOBJ = kinit.o
LDS = kernel.lds

INCLUDE += -I$(SRC_ROOT)/kernel

.PHONY := xiphos
xiphos: $(PACKAGE_NAME).img
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(PACKAGE_NAME).img: $(KOBJ)
	$(LD) $(LDFLAGS) -T $(LDS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

kinit.o: kinit.c

CLEAN = *.img *.o

.PHONY += clean
clean:
	$(_QUIET)$(RM) $(CLEAN)
