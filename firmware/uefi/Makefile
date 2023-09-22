.PHONY: _all
OBJ = reloc.o start.o

_all: $(OBJ)

reloc.o: reloc.c
	$(CC) $(UEFI_CFLAGS) $(INCLUDE) -o $@ -c $^

start.o: start.S
	$(CC) $(UEFI_CFLAGS) $(INCLUDE) -o $@ -c $^

clean:
	$(RM) *.o
