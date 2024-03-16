# Contributing to Xiphos
---
This doc helps getting started with contribuitng to Xiphos. It covers the build system, the repository structure,
conventions, languages, etc.


## Building Xiphos
This project uses GNU Make. One may invoke just 'make' to build Xiphos. 'make help' outputs the targets. scripts/check.sh
helps with setting up the building environment.

Requirements:
- make
- bash 
- x86_64-elf-gcc or clang
- ld or ld.lld
- fasm

Building Xiphos from its installation image is planned for the future, but it's not happening in the near future as
it requires porting some build system or making one from scratch for the system.


## Supported targets
The only supported target now is x86_64. ARM support is planned. Xiphos has a UEFI bootloader, but BIOS booting might be added if there's demand for it.


## Repository structure
- /boot - bootloader
- /devman - device manager
- /include - headers
- /kernel - the main source files of the kernel
  - /init - kernel startup code
  - /mem - memory management code
  - /sched - scheduler
- /libc - C standard library port
- /libos - hardware abstractions
- /utils - convenience scripts (only related to build system as of now)

The following directories are generated when building:
- /build - EFI file system with the bootloader and the kernel image
- /subsys - object files of major subsystems (demvan et al, used for linking)
- /*/obj - object files gathered from * subdirectory


## Programming languages
The main language of the kernel is C. The main assembler is FASM. Additional modules can be written in C++, Rust, Pascal or any other language, able to do low-level stuff and make freestanding flat binaries.


## Naming convintions 
Use snake_case for function names and function pointer typedefs(end those with _t).
Use camelCase for variable and structure names. Structure names should start with a capital letter(CamelCase).
Use SNAKE_CASE_WITH_CAPITAL_LETTERS for macros and enums.
Use single underscore prefix for thunks and stubs. Two underscores are usually for intrinsics.


## Major features of alpha edition
- VGA TUI for terminal
- Basic multitasking
- Basic device management
- PCI driver