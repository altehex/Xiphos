XMEM_DIRS := $(CONFIG_MALLOC)

XMEM_LOCAL_SOURCE_NAMES = info
XMEM_SOURCE_NAMES := $(CONFIG_MALLOC)

XMEM_LDS     =  mem.lds
XMEM_OBJ     := $(foreach OBJ, $(XMEM_SOURCE_NAMES), $(OBJ).o)
XMEM_LOCAL_OBJ :=  $(foreach OBJ, $(XMEM_LOCAL_SOURCE_NAMES), $(OBJ).o)

export XMEM_INCLUDE := $(INCLUDE) \
				       -I$(SRC_ROOT)/kernel/mem

.PHONY = all
all: $(XMEM_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(XMEM_ALL): $(XMEM_DIRS) $(XMEM_LOCAL_OBJ)
	$(LD) --relocatable -T $(XMEM_LDS) $(XMEM_OBJ) $(XMEM_LOCAL_OBJ) -o $@

.PHONY += $(XMEM_DIRS)
$(XMEM_DIRS): _force
	$(MAKE) -C $@

%.o: %.c
	$(CC) $(CFLAGS) $(XMEM_INCLUDE) -o $@ -c $^

CLEAN_DIRS := $(foreach DIR, $(XMEM_DIRS), $(addsuffix .clean,$(DIR)))
CLEAN_FILES = *.o *.c.*

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)
	$(RM) $(CLEAN_FILES)

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
