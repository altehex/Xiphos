KINIT_SOURCE_NAMES := acpi cpu irq kinit

KINIT_OBJ := $(foreach OBJ, $(KINIT_SOURCE_NAMES), $(OBJ).o)
KINIT_LDS = init.lds

INCLUDE += -I$(SRC_ROOT)/kernel/init

.PHONY += _all
_all: $(KINIT_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

init.o: $(KINIT_OBJ)
	$(LD) $(LDFLAGS) -T $(KINIT_LDS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

$(foreach NAME, $(KINIT_SOURCE_NAMES), \
	$(eval $(NAME).o: $(NAME).c))

CLEAN = *.o

clean:
	$(RM) $(CLEAN)
