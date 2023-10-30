KINIT_SOURCE_NAMES = kinit acpi irq
KINIT_API_FUNCTION_NAMES = video/$(API_VESA)/setup_vesa

KINIT_LDS = init.lds
KINIT_OBJ := $(foreach OBJ, $(KINIT_SOURCE_NAMES), $(OBJ).o) $(foreach API_FUNCTION, $(KINIT_API_FUNCTION_NAMES), $(SRC_ROOT)/api/$(API_FUNCTION).o)

INCLUDE += -I$(SRC_ROOT)/kernel/init

.PHONY += _all
_all: $(KINIT_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(KINIT_ALL): $(KINIT_OBJ)
	$(LD) --relocatable -T $(KINIT_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@ 

$(foreach NAME, $(KINIT_SOURCE_NAMES), \
	$(eval $(NAME).o: $(NAME).c))

CLEAN = *.o *.c.*

clean:
	$(RM) $(CLEAN)
