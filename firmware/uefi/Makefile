.PHONY := uefi
uefi: uefi.o

uefi.o: uefi.c 
	$(CC) $(CFLAGS) $(UEFI_CFLAGS) $(INCLUDE) -o uefi.o -c uefi.c

.PHONY += clean
clean:
	$(RM) *.o
