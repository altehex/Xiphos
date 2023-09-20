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

RM      = rm -f

# Verbosity configuration
#---------------------------*
ifeq ("$(origin v)", "command line")
	__VERBOSE = $(v)
endif

_QUIET   = @
_VERBOSE = --verbose
ifeq (1, $(__VERBOSE))
	_QUIET   =
	_VERBOSE = 
endif

MAKE := $(_QUIET)$(MAKE)
RM   := $(_QUIET)$(RM)

export _QUIET _VERBOSE RM MAKE
#-(end of verbosity configuration)---


# Toolchain configuration 
#--------------------------------*

ifeq (1,$(LLVM))
	TARGET ?= -target x86_64-pc-none

	CC		= $(_QUIET)clang $(TARGET)
	LD		= $(_QUIET)ld.lld
else
	CC		= $(_QUIET)gcc
	LD		= $(_QUIET)ld

endif

export CC LD
#-(end of toolchain configuration)---


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17                 \
		 -funsigned-char		 

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
	$(MAKE) -C kernel

.PHONY += bootloader
bootloader:
	$(MAKE) -C boot

.PHONY += dist
dist:
	# tar: compress the kernel image and the bootloader

.PHONY += clean
clean: MAKEFLAGS += --quiet
clean:
		$(MAKE) clean -C boot
		$(MAKE) clean -C firmware
		$(MAKE) clean -C kernel

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
		@echo   "Shhhh:                "$(_QUIET)
		@echo	""
		@echo   "User settings:"
		@echo   "* LLVM flag:            "$(LLVM)
		@echo	"* User-defined CFLAGS:  "$(USER_CFLAGS)
		@echo	"* User-defined LDFLAGS: "$(USER_LDFLAGS)
		@echo	""
		@echo   "Generated files:"
		@echo	"* Object files: "$(shell ls -R *.o)
