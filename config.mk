CONFIG_QUIET    = 0
CONFIG_VERBOSE  = 0 
CONFIG_DEBUG    = 0

CONFIG_LLVM = 0

USER_CFLAGS   = -O1 -march=native
USER_LDFLAGS  = -O1

include $(SRC_ROOT)/boot/config.mk
