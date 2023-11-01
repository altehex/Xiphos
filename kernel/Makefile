KERNEL_IMAGE_DIR  := $(SRC_ROOT)/build/efi/xiphos
KERNEL_IMAGE_NAME := $(PACKAGE_NAME).img

export KINIT_ALL = init.o

KERNEL_OBJ := $(KINIT_ALL) $(API_OBJ) $(LIBOS_OBJ)
KERNEL_LDS = kernel.lds

export KERNEL_INCLUDE := $(INCLUDE) \
						 -I$(SRC_ROOT)/kernel

CFLAGS += $(KERNEL_USER_CONFIG)

_DIRS = init
DIRS = $(foreach DIR, $(_DIRS),$(SRC_ROOT)/kernel/$(DIR))

.PHONY = all
all: $(KERNEL_IMAGE_NAME)
	$(MKDIR) -p $(KERNEL_IMAGE_DIR)
	$(CP) $^ $(KERNEL_IMAGE_DIR)/

# All objects linked here should be preliminarily linked with --relocatable flag
$(KERNEL_IMAGE_NAME): $(DIRS)
	$(LD) $(LDFLAGS) -T $(KERNEL_LDS) $(KERNEL_OBJ) -o $@

.PHONY += $(DIRS)
$(DIRS): _force
	$(MAKE) -C $@

CLEAN_DIRS := $(foreach DIR, $(DIRS), $(addsuffix .clean,$(DIR)))
CLEAN_FILES = *.img *.o *.c.*

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)
	$(RM) $(CLEAN_FILES)

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
