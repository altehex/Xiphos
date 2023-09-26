.PHONY := thanatos
thanatos: kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

kernel.o: kernel.c

.PHONY += clean
clean:
	$(_QUIET)$(RM) *.o
