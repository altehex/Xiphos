.PHONY := thanatos
thanatos: kernel.o

%.img:

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

thanatos-$(OS_EDITION_LATIN)-$(OS_VERSION).img:

kernel.o: kernel.c

.PHONY += clean
clean:
	$(_QUIET)$(RM) *.o
