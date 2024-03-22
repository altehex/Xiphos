include $(SRC_ROOT)/utils/macro.mk

MALLOC_NAME     = xiphos_std_free_list_malloc

ALL := $(MALLOC_NAME).o
SOURCE_NAMES = globals malloc init

OBJ := $(call OBJ_WRAP, $(SOURCE_NAMES))
LDS := ld.lds

__INCLUDE := $(XMEM_INCLUDE) \
		     -I$(call PWD) 

DEFINES := -D$(IMG_BASE)

.PHONY = all
all: $(ALL)
	$(CP) $^ $(SRC_ROOT)/kernel/$(MEMORY_DIR)

$(ALL): $(OBJ)
	$(LD) --relocatable -T $(LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(__INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
