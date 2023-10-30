# APIs act as a frontend, while libOSes are a backend

# Video
#----------------------------------*
export API_VESA = xiphos_std_vesa_api
export LIBOS_VESA = xiphos_std_vesa

CONFIG_HEADLESS = 0	# No graphics support

export _NAMES_API = video/$(API_VIDEO)
export _NAMES_LIBOS_ = video/$(LIBOS_VIDEO)
export _NAMES_CONFIG_ = CONFIG_HEADLESS

KERNEL_CONFIG_DEFINES := \
	$(foreach DEF, $(_NAMES_CONFIG_), $(intcmp $($(DEF)),1,,-D$(DEF)))

KERNEL_API_DEFINES := \
	$(foreach DEF, $(_NAMES_API_), -I$(SRC_ROOT)/api/$(DEF))

KERNEL_LIBOS_DEFINES := \
	$(foreach DEF, $(_NAMES_LIBOS_), -I$(SRC_ROOT)/libos/$(DEF))

export KERNEL_USER_CONFIG := $(KERNEL_CONFIG_DEFINES) $(KERNEL_LIBOS_DEFINES) $(KERNEL_API_DEFINES)
