include $(SRC_ROOT)/utils/macro.mk

LIBOS_NAME     = xiphos_std_pci_express
LIBOS_CATEGORY = serial/bus

XSTDPCIE_ALL := $(LIBOS_NAME).o
XSTDPCIE_SOURCE_NAMES = config

XSTDPCIE_OBJ := $(call OBJ_WRAP, $(XSTDPCIE_SOURCE_NAMES))
XSTDPCIE_LDS := $(LIBOS_NAME).lds

XSTDPCIE_INCLUDE := $(INCLUDE) \
				   -I$(call PWD)

.PHONY = all
all: $(XSTDPCIE_ALL)

$(XSTDPCIE_ALL): $(XSTDPCIE_OBJ)
	$(LD) --relocatable -T $(XSTDPCIE_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(XSTDPCIE_INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) *.o
