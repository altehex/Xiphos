#  Pefixes
#----------------------------------*
#  MAKE_:   variables for use in makefiles
#  LIBOS_:  libos of choice (xstd liboses are used by default)
#  CONFIG_: C defines for use in compilation
#  __:      misc variables which are not exported (for internal use)

#  Memory
#----------------------------------*

# Malloc implementation(should be in kernel/mem/)
export MAKE_MALLOC_IMPL = xiphos_std_free_list_malloc


#  Bus
#----------------------------------*

# PCI
CONFIG_PCI_SUPPORT = 1

ifeq (1,$(CONFIG_PCI_SUPPORT))
export LIBOS_PCI = xiphos_std_pci
endif

#  Serial
#----------------------------------*

# PCI Express
CONFIG_PCIE_SUPPORT = 0

ifeq (1,$(CONFIG_PCIE_SUPPORT))
export LIBOS_PCIE = xiphos_std_pci_express
endif

#  Video
#----------------------------------*

# Common settings
CONFIG_CONSOLE_OUTPUT = VGA # VGA is supported only as of now 

CONFIG_HEADLESS           = 0 # 1 for no graphics support
CONFIG_NO_LOGS_AT_STARTUP = 0 # Should the logs be printed at startup

# VGA
CONFIG_VGA_SUPPORT = 1

ifeq (VGA,$(CONFIG_CONSOLE_OUTPUT))
	CONFIG_VGA_SUPPORT := 1
endif

ifeq (1,$(CONFIG_VGA_SUPPORT))
export LIBOS_VGA = xiphos_std_vga
endif


#  Don't forget to make additions here
#  Keep the alphabetical order if possible

__LIBOS_LIST := $(LIBOS_PCI) $(LIBOS_PCIE) $(LIBOS_VGA) 

__Y_N_CONFIG = CONFIG_HEADLESS CONFIG_NO_LOGS_AT_STARTUP CONFIG_PCI_SUPPORT\
               CONFIG_PCIE_SUPPORT
__VAR_CONFIG = CONFIG_CONSOLE_OUTPUT CONFIG_MALLOC

export CONFIG_DEFINES := \
	$(foreach DEF, $(__Y_N_CONFIG),\
        $(intcmp $($(DEF)),1,,-D$(DEF)))\
	$(foreach DEF, $(__VAR_CONFIG),\
		-D$(DEF)=$($(DEF)))

export LIBOS_OBJ := \
	$(foreach LIBOS, $(__LIBOS_LIST),\
        $(i$(SRC_ROOT)/libos/obj/$(LIBOS).o))
