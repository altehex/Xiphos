KERNEL_IMAGE_DIR  := $(SRC_ROOT)/build/efi/xiphos
KERNEL_IMAGE_NAME := $(PACKAGE_NAME).img

export MEMORY_DIR = memory

export XINIT_ALL  = init.o
export XMEM_ALL   = $(MEMORY_DIR).o
export XSCHED_ALL = sched.o

KERNEL_SUBSYS = devman # shaman netman etc.
SUBSYS_OBJ := $(foreach SUBSYS,$(KERNEL_SUBSYS), \
			   $(SRC_ROOT)/subsys/$(SUBSYS).o)

KERNEL_OBJ := $(XINIT_ALL) $(XMEM_ALL) $(XSCHED_ALL) $(LIBOS_OBJ) $(SUBSYS_OBJ)
KERNEL_LDS = kernel.lds

export INCLUDE += -I$(SRC_ROOT)/kernel

CFLAGS += $(CONFIG_DEFINES)

DIRS = $(MEMORY_DIR) sched init

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
