KERNEL_IMAGE_DIR=$(SRC_ROOT)/build/efi/xiphos

export KINIT_ALL = init.o

KERNEL_OBJ = $(KINIT_ALL)
KERNEL_LDS = kernel.lds

INCLUDE += -I$(SRC_ROOT)/kernel

.PHONY := xiphos
xiphos: $(PACKAGE_NAME).img
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(PACKAGE_NAME).img: _init
	$(LD) $(LDFLAGS) -T $(KERNEL_LDS) -o $@ $(KERNEL_OBJ)

_init:
	$(MAKE) -C init

CLEAN = *.img *.o
DIRS = init

clean:
	$(foreach DIR, $(DIRS), \
		$(MAKE) clean -C $(DIR))
	$(RM) $(CLEAN)
