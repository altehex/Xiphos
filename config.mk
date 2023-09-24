CONFIG_QUIET    = 0
CONFIG_VERBOSE  = 0 
CONFIG_DEBUG    = 0

CONFIG_LLVM = 0

USER_CFLAGS   = -O2 -march=native
USER_LDFLAGS  =

include $(SRC_ROOT)/boot/config.mk
