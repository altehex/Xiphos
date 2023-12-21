include $(SRC_ROOT)/utils/macro.mk

LIBC = lib.o
SOURCE_NAMES = malloc

OBJ = $(call OBJ_WRAP,$(SOURCE_NAMES))

.PHONY = all
all: $(LIBC)

$(LIBC): $(OBJ)
	$(LD) --relocatable $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
