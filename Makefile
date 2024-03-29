export OS_NAME            =  Xiphos
export OS_VERSION_MAJOR_L =  alpha
	   OS_VERSION_MAJOR   =  α
	   OS_VERSION_MINOR   =  2.3
export OS_VERSION         := $(OS_VERSION_MAJOR_L)-$(OS_VERSION_MINOR)
export PACKAGE_NAME       := xiphos-$(OS_VERSION)


include utils/macro.mk

export SRC_ROOT := $(call PWD)

# User settings
include $(SRC_ROOT)/config.mk
include $(SRC_ROOT)/mem_layout.mk


MAKEFLAGS += -rR

unexport LC_ALL
export LC_COLLATE = C
export LC_NUMERIC = C

ifeq (1, $(CONFIG_QUIET))
	MAKEFLAGS += -s
endif


# Toolchain configuration 
#--------------------------------*
export RM    = rm -f
export CP    = cp -r
export MKDIR = mkdir
export MV    = mv
export TAR   = tar
export ZIP   = gzip

export TARGET = x86_64-elf

ifeq (1,$(CONFIG_LLVM))
	CC		:= clang -target $(TARGET)
	LD		:= ld.lld
else
	CC		:= $(TARGET)-gcc
	LD		:= $(TARGET)-ld
endif
export FASM 	= fasm

ifeq (1,$(CONFIG_DEBUG))
	CC   += -g -dp -fopt-info-all -flto-report
	FASM += -s $@.fas
endif

export CC LD


# Flags configuration 
#---------------------------------*
CFLAGS = -std=c17 \
         -nostdlib \
         -nolibc \
         -mno-red-zone \
	     -ffreestanding \
		 -funsigned-char

CWARNINGS = -Wall \
		    -Wextra 

LDFLAGS = -ffreestanding \
		  -shared \
		  -nostdlib \
		  --gc-sections

ifeq (1, $(CONFIG_DEBUG))
	CWARNINGS += -Wpadded
endif

export CFLAGS  += $(USER_CFLAGS) $(CWARNINGS)
export LDFLAGS += $(USER_LDFLAGS)

export INCLUDE := -I$(SRC_ROOT) \
		   -I$(SRC_ROOT)/include \
		   -I$(SRC_ROOT)/libc


# Targets
#-------------------------------*

# boot is supposed to be last
DIRS = libos devman kernel boot
ROOT_FILES = config.mk CHANGELOG.md CONTRIBUTING.md Makefile \
             mem_layout.mk README.md TODO.md

.PHONY = all
all: $(DIRS)

.PHONY += $(DIRS)
$(DIRS): check_build_dir
	$(MAKE) -C $@

.PHONY += check_build_dir
check_build_dir: _force
	[[ -e build ]]  || $(MKDIR) build
	[[ -e subsys ]] || $(MKDIR) subsys

.PHONY += dist
dist: _force
	[[ -e $(PACKAGE_NAME) ]] || $(MKDIR) $(PACKAGE_NAME)
	$(CP) -R $(DIRS) $(ROOT_FILES) libc utils $(PACKAGE_NAME)
	$(TAR) -cf $(PACKAGE_NAME).tar $(PACKAGE_NAME)
	$(ZIP) $(PACKAGE_NAME).tar
	$(RM) -rf $(PACKAGE_NAME)

CLEAN_DIRS := $(foreach DIR,$(DIRS),$(addsuffix .clean,$(DIR)))

.PHONY += $(CLEAN_DIRS) clean
clean: MAKEFLAGS += -s
clean: $(CLEAN_DIRS)
	$(RM) -r build
	$(RM) -r subsys
	$(RM) *.tar.*

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
