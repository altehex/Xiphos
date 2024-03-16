# To-dos
---

## Major features of alpha edition
- VGA TUI for terminal
- Basic multitasking
- Basic device management
- PCI driver

## Goals for alpha-3
- [ ] Basic PCI support
- [ ] VGA initialization, basic text mode output (just for logging)
- [ ] Kernel initialization on every core
- [X] Basic memory allocation: *(as of March 2024)* free-list allocator is implemented
- [ ] Basic parallelism

## Future goals
- Basic I/O (might be implemented prior to alpha-3)
- Russian language

## VGA
- Add VGA via PCI support

## Bootloader and xinit
- Parse ACPI tables
- Make feature checks
- Add 2 MB paging
- Fix StartupThisAP in smp.asm, so BSP won't jump into abyss

## Security
- Prevent stack smashing
- Prevent buffer overflows for allocated memory

## Build system
- Improve check.sh (so it won't reevaluate if files exist twice)
- Add other systems to install_gcc.sh


