KERNEL_IMAGE_DIR  = $(SRC_ROOT)/build/efi/xiphos
KERNEL_IMAGE_NAME = $(PACKAGE_NAME).img

export KINIT_ALL = init.o

export KERNEL_OBJ := $(KINIT_ALL)
KERNEL_LDS = kernel.lds

export KERNEL_INCLUDE = $(INCLUDE) \
						-I$(SRC_ROOT)/kernel

CFLAGS += $(KERNEL_USER_CONFIG)

.PHONY := xiphos
xiphos: $(KERNEL_IMAGE_NAME)
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

$(KERNEL_IMAGE_NAME): api _init
	$(LD) $(LDFLAGS) -T $(KERNEL_LDS) -o $@ $(KERNEL_OBJ)

api:
# Gotta come up with some macros
# 	$(foreach LIBOS_PATH, $(_NAMES_LIBOS_),	\
# 		$(MAKE) -C $(SRC_ROOT)/libos/$(LIBOS_PATH))
	$(MAKE) -C $(SRC_ROOT)/api/video/xiphos_std_vesa_api

_init:
	$(MAKE) -C init

CLEAN_EXT = *.img *.o *.c.*
CLEAN_DIRS = init
clean:
	$(MAKE) clean -C init
	$(RM) $(CLEAN_EXT)
