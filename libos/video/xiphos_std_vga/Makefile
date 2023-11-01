include $(SRC_ROOT)/utils/macro.mk

LIBOS_NAME     = xiphos_std_vga
LIBOS_CATEGORY = video

XIPHOS_STD_VGA_ALL := $(LIBOS_NAME).o
XIPHOS_STD_VGA_SOURCE_NAMES = crt

XIPHOS_STD_VGA_OBJ := $(call OBJ_WRAP, $(XIPHOS_STD_VGA_SOURCE_NAMES))
XIPHOS_STD_VGA_LDS := $(LIBOS_NAME).lds

XIPHOS_STD_VGA_INCLUDE := $(INCLUDE) \
						  -I$(call PWD)

.PHONY = all
all: $(XIPHOS_STD_VGA_ALL)

$(XIPHOS_STD_VGA_ALL): $(XIPHOS_STD_VGA_OBJ)
	$(LD) --relocatable -T $(XIPHOS_STD_VGA_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(XIPHOS_STD_VGA_INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
