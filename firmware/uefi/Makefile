UEFI_CFLAGS = -fno-stack-protector   \
			  -mno-red-zone          \
			  -DEFI_FUNCTION_WRAPPER

.PHONY := uefi
uefi: uefi.o

uefi.o: uefi.c 
	$(_QUIET)$(CC) $(CFLAGS) $(UEFI_CFLAGS) $(INCLUDE) -o uefi.o -c uefi.c

.PHONY += clean
clean:
	$(_QUIET)$(RM) *.o
