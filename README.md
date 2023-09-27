![Static Badge](https://img.shields.io/badge/ThanatOS-%CE%B1--0.0-262431)
[![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/altehex/ThanatOS/c-cpp.yml?branch=master)](https://github.com/altehex/ThanatOS/actions/workflows/c-cpp.yml)

Run with:
```bash
qemu-system-x86_64 -machine cpu35 -vga std -net none -usb -device usb-tablet \
                   -m <MEMORY> -cpu host -enable-kvm -nodefaults -smp 1,cores=<CORES> \
                   -global isa-debugicon.iobase=0x402 \
                   -drive if=pflash,format=raw,unit=0,readonly=on,file=<OVMF_PREFIX>/OVMF_CODE.fd \
                   -drive if=pflash,format=raw,unit=1,file=<OVMF_PREFIX>/OVMF_VARS.fd \
                   -drive file=fat:rw:build,format=raw 
```
