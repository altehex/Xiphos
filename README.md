![Static Badge](https://img.shields.io/badge/Xiphos-%CE%B1--2.3-262431)

Run with:
```bash
qemu-system-x86_64 -machine cpu35 -vga std -net none -usb -device usb-tablet \
                   -m <MEMORY> -cpu host -enable-kvm -nodefaults -smp <N>,cores=<CORES> \
                   -global isa-debugicon.iobase=0x402 \
                   -drive if=pflash,format=raw,unit=0,readonly=on,file=<OVMF_PREFIX>/OVMF_CODE.fd \
                   -drive if=pflash,format=raw,unit=1,file=<OVMF_PREFIX>/OVMF_VARS.fd \
                   -drive file=fat:rw:build,format=raw 
```
