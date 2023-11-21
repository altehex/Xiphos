export OS_NAME          =  Xiphos
	   OS_VERSION_MAJOR =  0
	   OS_VERSION_MINOR =  2.2
export OS_VERSION       := $(OS_VERSION_MAJOR).$(OS_VERSION_MINOR)
export OS_EDITION       =  α
export OS_EDITION_LATIN =  alpha
export PACKAGE_NAME     := xiphos-$(OS_EDITION_LATIN)-$(OS_VERSION)
TARNAME := $(PACKAGE_NAME).tar.xz
ISONAME := $(PACKAGE_NAME).iso


include utils/macro.mk

export SRC_ROOT := $(call PWD)

# User settings
include $(SRC_ROOT)/config.mk
include $(SRC_ROOT)/mem_layout.mk


MAKEFLAGS += -rR

unexport LC_ALL
export LC_COLLATE = C
export LC_NUMERIC = C


RM      = rm -f
CP      = cp -r
MKDIR   = mkdir
MV		= mv

ifeq (1, $(CONFIG_QUIET))
	MAKEFLAGS += -s
endif

export RM CP MKDIR MV


# Toolchain configuration 
#--------------------------------*
TARGET = x86_64-elf

ifeq (1,$(CONFIG_LLVM))
	CC		:= clang -target $(TARGET)
	LD		:= ld.lld
else
	CC		:= $(TARGET)-gcc
	LD		:= $(TARGET)-ld
endif
FASM 	= fasm
OBJCOPY = objcopy

ifeq (1,$(CONFIG_DEBUG))
	CC   += -g -dp -fopt-info-optimized-note -flto-report
	FASM += -s $@.fas
endif

export CC LD FASM OBJCOPY TARGET


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17 \
		 -funsigned-char \
         -nostdlib \
         -nolibc \
         -mno-red-zone \
	     -ffreestanding

CWARNINGS = -Wall \
		    -Wextra 

LDFLAGS = -ffreestanding \
		  -shared \
		  -nostdlib \
		  --gc-sections

ifeq (1, $(CONFIG_DEBUG))
	CWARNINGS += -Wpadded
endif

CFLAGS  += $(USER_CFLAGS) $(CWARNINGS)
LDFLAGS += $(USER_LDFLAGS)

INCLUDE := -I$(SRC_ROOT) \
		   -I$(SRC_ROOT)/include \
		   -I$(SRC_ROOT)/libc


export CFLAGS LDFLAGS INCLUDE


# Targets
#-------------------------------*
# The ordering is important (boot is last and kernel is second-to-last)
_DIRS = api libos devman kernel boot
DIRS := $(foreach DIR,$(_DIRS),$(SRC_ROOT)/$(DIR))

.PHONY = all
all: $(DIRS)

.PHONY += $(DIRS)
# check_build_dir is like a force target
$(DIRS): check_build_dir
	$(MAKE) -C $@

.PHONY += check_build_dir
check_build_dir: _force
	[[ -e build ]] || mkdir build
	[[ -e subsys ]] || mkdir subsys

.PHONY += dist
dist: # tar: compress the kernel image and the bootloader

CLEAN_DIRS := $(foreach DIR,$(DIRS),$(addsuffix .clean,$(DIR)))

.PHONY += $(CLEAN_DIRS) clean
clean: MAKEFLAGS += -s
clean: $(CLEAN_DIRS)
	$(RM) -r build
	$(RM) -r subsys

$(CLEAN_DIRS):
	$(MAKE) clean -C $(basename $@)

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
		@echo   "    test        - for developers. Outputs flags and general settings"

.PHONY += test
test: MAKEFLAGS += -s
test:
		@echo   "Project name:         "$(OS_NAME) $(OS_EDITION)-$(OS_VERSION)
		@echo   "Tarball name:         "$(TARNAME)
		@echo 	"C compiler:           "$(CC)
		@echo   "Linker:               "$(LD)
		@echo   "CFLAGS:               "$(CFLAGS) 
		@echo   "LDFLAGS:              "$(LDFLAGS)
		@echo	""
		@echo   "User settings:"
		@echo   "* LLVM flag:            "$(CONFIG_LLVM)

_force: ;
