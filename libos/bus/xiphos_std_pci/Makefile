include $(SRC_ROOT)/utils/macro.mk

LIBOS_NAME     = xiphos_std_pci

ALL := $(LIBOS_NAME).o
# SOURCE_NAMES = memory setup_video

# LIBOS = 
# OBJ := $(call OBJ_WRAP, $(SOURCE_NAMES))
# LDS := $(LIBOS_NAME).lds

# _INCLUDE := $(INCLUDE) \
# 		   -I$(call PWD) \
# 		   $(call PREFIX_INCLUDE_WRAP,$(LIBOS),$(SRC_ROOT)/libos)

.PHONY = all
all: $(ALL)

$(ALL): $(OBJ)
# 	$(LD) --relocatable -T $(LDS) $^ -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) $(_INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
