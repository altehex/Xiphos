# XSTDVGA cheatsheet
---

## Header files
- `define.h`: constants and macros (port numbers are here)
- `include/asm.h`: inline assembly code (`in()`, `out()`, etc.)

## Output to port

### Selecting a register
```c
	out(<PORT_NUMBER>, <INDEX>)
```
