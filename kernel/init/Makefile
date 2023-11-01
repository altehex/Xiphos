KINIT_SOURCE_NAMES = kinit acpi irq

KINIT_LDS     =  init.lds
KINIT_API     := console/$(API_CONSOLE)
KINIT_LIBOS   := video/$(LIBOS_VGA)
KINIT_OBJ     := $(foreach OBJ, $(KINIT_SOURCE_NAMES), $(OBJ).o)

VPATH = .:$(SRC_ROOT)/api
INCLUDE += -I$(SRC_ROOT)/kernel/init \
		   $(foreach API, $(KINIT_API), -I$(SRC_ROOT)/api/$(API)) \
		   $(foreach LIBOS, $(KINIT_LIBOS), -I$(SRC_ROOT)/libos/$(LIBOS))

.PHONY = all
all: $(KINIT_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

# Don't forget to try to use vpath for api and libos objects
$(KINIT_ALL): $(KINIT_OBJ)
	$(LD) --relocatable -T $(KINIT_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@ 

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
