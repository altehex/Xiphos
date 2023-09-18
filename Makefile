export OS_NAME    = ThanatOS
export OS_VERSION = alpha-0.0

export SRC_ROOT := .

# User settings
include $(SRC_ROOT)/config.mk


MAKEFLAGS += -rR

unexport LC_ALL
export LC_COLLATE = C
export LC_NUMERIC = C

# Verbosity configuration
#---------------------------*
ifeq ("$(origin v)", "command line")
	_VERBOSE = $(v)
endif

ifneq ($(findstring 1, $(_VERBOSE)),)
	_ECHO = @
else
	ifneq ($(findstring 2, $(_VERBOSE)),)
		_ECHO = @
		# have to come up with the way comments are invoked
	else
		_ECHO =
	endif
endif

#-(end of verbosity configuration)---

# Toolchain configuration 
#--------------------------------*
ifneq ($(LLVM),)
ifneq ($(filter %/, $(LLVM)),)
	LLVM_PREFIX ?= $(LLVM)
else ifneq ($(filter -%,$(LLVM)),)
	LLVM_SUFFIX ?= $(LLVM)
endif
endif

ifneq ($(LLVM),)
	CC		?= $(LLVM_PREFIX)clang$(LLVM_SUFFIX)
	LD		?= $(LLVM_PREFIX)ld.lld$(LLVM_SUFFIX)
else
	CC		?= $(CROSS_COMPILE)gcc
	LD		?= $(CROSS_COMPILE)ld
endif
#-(end of toolchain configuration)---

export INCLUDE := -I$(SRC_ROOT)/include

# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17                 \
         -Wall                    \
         -funsigned-char

LDFLAGS = 

CFLAGS  += $(USER_CFLAGS)
LDFLAGS += $(USER_LDFLAGS)

export CFLAGS LDFLAGS
#-(end of flags configuration)--------

.PHONY := all
all: kernel bootloader

.PHONY += kernel
kernel:
	$(_ECHO)$(MAKE) -C kernel

.PHONY += bootloader
bootloader:
	$(_ECHO)$(MAKE) -C boot

.PHONY += clean
clean:

.PHONY += help
help:
		@echo   "config.mk is a global configuration file, containing user settings"
		@echo   "and putting together config.mk's from other subdirectories."
		@echo   ""
		@echo   "Targets:"
		@echo   "    all         - build both the kernel and the bootloader"
		@echo   "    kernel      - build the kernel"
		@echo   "    bootloader  - build the bootloader"
		@echo   "    clean       - remove generated files"
		@echo	""
		@echo	"Set v=1 to echo every command, v=2 to output comments, if there are any"

