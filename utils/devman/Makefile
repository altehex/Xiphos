include $(SRC_ROOT)/utils/macro.mk

MODULE_NAME = devman

ALL = $(MODULE_NAME).o
SOURCE_NAMES = acpi device_db

OBJ := $(call OBJ_WRAP, $(SOURCE_NAMES))
LDS := $(MODULE_NAME).lds

.PHONY = all
all: $(ALL)
	$(CP) $(ALL) $(SRC_ROOT)/subsys/

_INCLUDE := $(INCLUDE) \
		   -I$(call PWD)

$(ALL): $(OBJ)
	$(LD) --relocatable -T $(LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(_INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
