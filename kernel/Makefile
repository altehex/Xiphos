KERNEL_IMAGE_DIR=$(SRC_ROOT)/build/efi/thanatos
LD_SCRIPT=$(SRC_ROOT)/kernel/kernel.lds

OBJ = kernel.o

.PHONY := thanatos
thanatos: $(PACKAGE_NAME).img
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(PACKAGE_NAME).img:: $(OBJ)
	$(LD) $(LDFLAGS) -T $(LD_SCRIPT) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^


kernel.o: kernel.c

.PHONY += clean
clean:
	$(_QUIET)$(RM) *.o
