# APIs act as a frontend, while libOSes are a backend

# Video
#----------------------------------*
export API_CONSOLE = console/xiphos_std_console  # text mode API

export LIBOS_VGA   = video/xiphos_std_vga        # VGA library

CONFIG_HEADLESS = 0 			# 1 for no graphics support
CONFIG_NO_LOGS_AT_STARTUP = 0	# Should the logs be printed at startup

# Don't touch this
export _NAMES_Y_N_CONFIG_ = CONFIG_HEADLESS CONFIG_NO_LOGS_AT_STARTUP 

export KERNEL_CONFIG_DEFINES := \
	$(foreach DEF, $(_NAMES_Y_N_CONFIG_), $(intcmp $($(DEF)),1,,-D$(DEF)))
