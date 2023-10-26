export OS_NAME          = Xiphos
	   OS_VERSION_MAJOR = 0
	   OS_VERSION_MINOR = 1
export OS_VERSION       = $(OS_VERSION_MAJOR).$(OS_VERSION_MINOR)
export OS_EDITION       = α
export OS_EDITION_LATIN = alpha
export PACKAGE_NAME     = xiphos-$(OS_EDITION_LATIN)-$(OS_VERSION)
TARNAME := $(PACKAGE_NAME).tar.xz


export SRC_ROOT := $(shell pwd)

# User settings
include $(SRC_ROOT)/config.mk
include $(SRC_ROOT)/mem_layout.mk


MAKEFLAGS += -rR

unexport LC_ALL
export LC_COLLATE = C
export LC_NUMERIC = C

RM      = rm -f
CP      = cp
MKDIR   = mkdir
MV		= mv

VERBOSE := 
DEBUG :=
ifeq (1, $(CONFIG_VERBOSE))
	VERBOSE := --verbose
endif

ifeq (1, $(CONFIG_QUIET))
	MAKEFLAGS += -s
endif

export VERBOSE RM CP MKDIR MV


# Toolchain configuration 
#--------------------------------*
TARGET = x86_64-elf

ifeq (1,$(CONFIG_LLVM))
	CC		= clang $(VERBOSE) $(DEBUG) -target $(TARGET)
	LD		= ld.lld $(VERBOSE)
else
	CC		= $(TARGET)-gcc
	LD		= $(CC)
endif
FASM 	= fasm
OBJCOPY = objcopy

ifeq (1, $(CONFIG_DEBUG))
	CC   += -g
	FASM += -s $@.fas
endif

export CC LD FASM TARGET OBJCOPY
#-(end of toolchain configuration)---


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17 \
		 -funsigned-char

CWARNINGS = -Wall \
		    -Wextra

LDFLAGS = -ffreestanding \
		  -shared \
		  -nostdlib \
		  -lgcc

ifeq (1, $(CONFIG_DEBUG))
	CWARNINGS += -Wpadded
endif

CFLAGS  += $(USER_CFLAGS) $(CWARNINGS)
LDFLAGS += $(USER_LDFLAGS)
CPPFLAGS := $(CFLAGS)

INCLUDE := -I$(SRC_ROOT)/include


export CFLAGS LDFLAGS INCLUDE
#-(end of flags configuration)--------


# Targets
#-------------------------------*
.PHONY := __all
__all: check_build_dir all

.PHONY += check_build_dir
check_build_dir:
	[[ -e build ]] || mkdir build

.PHONY += all
all: _kernel bootloader

.PHONY += _kernel
_kernel:
	$(MAKE) -C kernel

.PHONY += bootloader
bootloader:
	$(MAKE) -C boot

.PHONY += dist
dist:
	# tar: compress the kernel image and the bootloader

clean:
	$(MAKE) clean -C boot
	$(MAKE) clean -C kernel
	$(RM) -r build

help: MAKEFLAGS += -s
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

test: MAKEFLAGS += -s
test:
		@echo   "Project name:         "$(OS_NAME) $(OS_EDITION)-$(OS_VERSION)
		@echo   "Tarball name:         "$(TARNAME)
		@echo 	"C compiler:           "$(CC)
		@echo   "Linker:               "$(LD)
		@echo   "CFLAGS:               "$(CFLAGS) 
		@echo   "LDFLAGS:              "$(LDFLAGS)
		@echo	"Source directory:     "$(SRC_ROOT)
		@echo   "Included directories: "$(INCLUDE)
		@echo	""
		@echo   "User settings:"
		@echo   "* LLVM flag:            "$(CONFIG_LLVM)
		@echo	"* User-defined CFLAGS:  "$(USER_CFLAGS)
		@echo	"* User-defined LDFLAGS: "$(USER_LDFLAGS)
		@echo	""
		@echo	"Bootloader:"
		@$(MAKE) test -C boot
