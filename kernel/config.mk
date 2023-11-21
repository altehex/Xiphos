# APIs act as a frontend, while libOSes are a backend


# Memory
#----------------------------------*
export CONFIG_MALLOC = xiphos_std_free_list_malloc    # Malloc implementation(should be in kernel/mem/)


# Bus
#----------------------------------*
export LIBOS_PCIE = xiphos_std_pci_express


# Video
#----------------------------------*
export API_CONSOLE = xiphos_std_console  # text mode API

export LIBOS_VGA   = xiphos_std_vga      # VGA library

API_LIST   := $(API_CONSOLE)
LIBOS_LIST := $(LIBOS_VGA)

CONFIG_HEADLESS           = 0 	# 1 for no graphics support
CONFIG_NO_LOGS_AT_STARTUP = 1	# Should the logs be printed at startup


# Don't touch this
#----------------------------------*
export __NAMES_Y_N_CONFIG = CONFIG_HEADLESS CONFIG_NO_LOGS_AT_STARTUP 
export __NAMES_VAR_CONFIG = CONFIG_MALLOC

export KERNEL_CONFIG_DEFINES := \
	$(foreach DEF,$(__NAMES_Y_N_CONFIG),$(intcmp $($(DEF)),1,,-D$(DEF)))

export API_OBJ :=  \
	$(foreach API, $(API_LIST),$(SRC_ROOT)/api/obj/$(API).o)
export LIBOS_OBJ :=  \
	$(foreach LIBOS, $(LIBOS_LIST),$(SRC_ROOT)/libos/obj/$(LIBOS).o)
