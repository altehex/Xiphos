CONFIG_QUIET    = 0
CONFIG_VERBOSE  = 0
CONFIG_DEBUG    = 0

CONFIG_LLVM = 0

USER_CFLAGS   = -O2 -march=x86-64
USER_LDFLAGS  = -O2

CONFIG_MK = config.mk

include kernel/$(CONFIG_MK)