XMEM_SOURCE_NAMES = malloc

XMEM_LDS     =  mem.lds
XMEM_OBJ     := $(foreach OBJ, $(XMEM_SOURCE_NAMES), $(OBJ).o)

XMEM_INCLUDE := $(INCLUDE) \
				  -I$(SRC_ROOT)/kernel/mem

.PHONY = all
all: $(XMEM_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(XMEM_ALL): $(XMEM_OBJ)
	$(LD) --relocatable -T $(XMEM_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(XMEM_INCLUDE) -c $^ -o $@ 

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
