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
CP      = cp
MV		= mv

VERBOSE := 
DEBUG :=
ifeq (1, $(CONFIG_VERBOSE))
	VERBOSE := --verbose
endif

ifeq (1, $(CONFIG_QUIET))
	MAKEFLAGS += -s
endif

export VERBOSE RM CP MV


# Toolchain configuration 
#--------------------------------*
TARGET = x86_64-pc-none

ifeq (1,$(CONFIG_LLVM))
	CC		= clang $(VERBOSE) $(DEBUG)
	CPP     = clang++ $(VERBOSE) $(DEBUG)
	LD		= ld.lld $(VERBOSE)
else
	CC		= gcc
	CPP     = g++
	LD		= ld
endif
FASM = fasm

ifeq (1, $(CONFIG_DEBUG))
	CC   += -g
	FASM += -s $@.fas
endif

export CC LD FASM TARGET
#-(end of toolchain configuration)---


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17 \
		 -funsigned-char

CWARNINGS = -Wall \
		    -Wextra

LDFLAGS = 

CFLAGS  += $(USER_CFLAGS)$(CWARNINGS)
LDFLAGS += $(USER_LDFLAGS)
CPPFLAGS := $(CFLAGS)

INCLUDE := -I$(SRC_ROOT)/include

export CFLAGS LDFLAGS INCLUDE
#-(end of flags configuration)--------


# Targets
#-------------------------------*
.PHONY := all
all: bootloader kernel

.PHONY += kernel
kernel: CC += $(if $(CONFIG_LLVM), -target $(TARGET))
kernel: LD += $(if $(CONFIG_LLVM), -target $(TARGET))
kernel:
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
	$(RM) build/*

.PHONY += help
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
		@echo	""
		@echo	"Set v=1 to echo every command"

.PHONY += test
test:
		@echo   "Project name:         "$(OS_NAME) $(OS_EDITION)-$(OS_VERSION)
		@echo   "Tarball name:         "$(TARNAME)
		@echo 	"C compiler:           "$(CC)
		@echo   "C++ compiler          "$(CPP)
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
