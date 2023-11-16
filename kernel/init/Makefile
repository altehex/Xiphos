XINIT_SOURCE_NAMES = xinit

XINIT_LDS     =  init.lds
XINIT_API     := console/$(API_CONSOLE)
XINIT_LIBOS   := video/$(LIBOS_VGA) serial/bus/$(LIBOS_PCIE)
XINIT_OBJ     := $(foreach OBJ, $(XINIT_SOURCE_NAMES), $(OBJ).o)

XINIT_INCLUDE := $(INCLUDE) \
				 -I$(SRC_ROOT)/kernel/init \
		   		 $(foreach API, $(XINIT_API), -I$(SRC_ROOT)/api/$(API)) \
		   		 $(foreach LIBOS, $(XINIT_LIBOS), -I$(SRC_ROOT)/libos/$(LIBOS))

.PHONY = all
all: $(XINIT_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(XINIT_ALL): $(XINIT_OBJ)
	$(LD) --relocatable -T $(XINIT_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(XINIT_INCLUDE) -c $^ -o $@ 

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
