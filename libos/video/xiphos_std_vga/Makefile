include $(SRC_ROOT)/utils/macro.mk

LIBOS_NAME     = xiphos_std_vga
LIBOS_CATEGORY = video

XSTDVGA_ALL := $(LIBOS_NAME).o
XSTDVGA_SOURCE_NAMES = # Nothing to link for now

XSTDVGA_OBJ := _force $(call OBJ_WRAP, $(XSTDVGA_SOURCE_NAMES))
XSTDVGA_LDS := $(LIBOS_NAME).lds

XSTDVGA_INCLUDE := $(INCLUDE) \
				   -I$(call PWD)

.PHONY = all
all: $(XSTDVGA_ALL)

$(XSTDVGA_ALL): _force $(XSTDVGA_OBJ)
	touch $(XSTDVGA_ALL)
# $(LD) --relocatable -T $(XSTDVGA_LDS) $^ -o $@

_force: ;

%.o: %.c
	$(CC) $(CFLAGS) $(XSTDVGA_INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
