export OS_NAME    = ThanatOS
export OS_VERSION = 0.0
export OS_EDITION = alpha
TARNAME := thanatos-$(OS_EDITION)-$(OS_VERSION).tar.xz


export SRC_ROOT := $(shell pwd)

# User settings
include $(SRC_ROOT)/config.mk


MAKEFLAGS += -rR

unexport LC_ALL
export LC_COLLATE = C
export LC_NUMERIC = C


# Verbosity configuration
#---------------------------*
ifeq ("$(origin v)", "command line")
	__VERBOSE = $(v)
endif

_ECHO    = @
_VERBOSE = --verbose
ifneq ($(findstring 1, $(_VERBOSE)),)
	_ECHO =
	_VERBOSE = 
endif

export _ECHO
#-(end of verbosity configuration)---


# Toolchain configuration 
#--------------------------------*

ifeq (1,$(LLVM))
	TARGET ?= -target x86_64-pc-none

	CC		= clang $(TARGET)
	LD		= ld.lld
else
	CC		= gcc
	LD		= ld

endif

export CC LD
#-(end of toolchain configuration)---


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17                 \
		 -funsigned-char		  \
		 -fshort-wchar

CWARNINGS = -Wall                 \
		    -Wextra               \

LDFLAGS = 

CFLAGS  += $(USER_CFLAGS) $(CWARNINGS)
LDFLAGS += $(USER_LDFLAGS)

INCLUDE := -I$(SRC_ROOT)/include

export CFLAGS LDFLAGS INCLUDE
#-(end of flags configuration)--------


# Targets
#-------------------------------*
.PHONY := all
all: kernel bootloader

.PHONY += kernel
kernel:
	$(_ECHO)$(MAKE) -C kernel

.PHONY += bootloader
bootloader:
	$(_ECHO)$(MAKE) -C boot

.PHONY += dist
dist:
	# tar: compress the kernel image and the bootloader

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
		@echo   "    dist        - compress the kernel and the bootloader"
		@echo   "    clean       - remove generated files"
		@echo   "    test        - for developers. Outputs make variables"
		@echo	""
		@echo	"Set v=1 to echo every command"

.PHONY += test
test:
		@echo   "Project name:         "$(OS_NAME) $(OS_EDITION)-$(OS_VERSION)
		@echo   ".tar.xz name:         "$(TARNAME)
		@echo 	"Compiler:             "$(CC)
		@echo   "Linker:               "$(LD)
		@echo   "CFLAGS:               "$(CFLAGS) 
		@echo   "LDFLAGS:              "$(LDFLAGS)
		@echo	"Source directory:     "$(SRC_ROOT)
		@echo   "Included directories: "$(INCLUDE)
		@echo	""
		@echo   "User settings:"
		@echo   "* LLVM flag:            "$(LLVM)
		@echo	"* User-defined CFLAGS:  "$(USER_CFLAGS)
		@echo	"* User-defined LDFLAGS: "$(USER_LDFLAGS)
