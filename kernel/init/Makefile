KINIT_SOURCE_NAMES = kinit acpi irq

KINIT_LDS =  init.lds
KINIT_OBJ := $(foreach OBJ, $(KINIT_SOURCE_NAMES), $(OBJ).o)
KINIT_API =  $(API_CONSOLE)

INCLUDE += -I$(SRC_ROOT)/kernel/init \
		   $(foreach API, $(KINIT_API), -I$(SRC_ROOT)/api/$(API))

.PHONY = all
all: $(KINIT_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

# Don't forget to try to use vpath for api and libos objects
$(KINIT_ALL): $(KINIT_OBJ)
	$(LD) --relocatable -T $(KINIT_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@ 

# $(foreach NAME, $(KINIT_SOURCE_NAMES), \
# 	$(eval $(NAME).o: $(NAME).c))

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
