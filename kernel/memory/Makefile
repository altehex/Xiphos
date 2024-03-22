XMEM_DIRS := $(MAKE_MALLOC_IMPL)

XMEM_LDS            =  mem.lds
XMEM_COMMON_SOURCES =  mem_globals.c
XMEM_COMMON_OBJ     := $(XMEM_COMMON_SOURCES:.c=.o)
XMEM_MALLOC_SOURCES := $(MAKE_MALLOC_IMPL).c
XMEM_MALLOC_OBJ     := $(XMEM_MALLOC_SOURCES:.c=.o)

export XMEM_INCLUDE := $(INCLUDE) \
				       -I$(SRC_ROOT)/kernel/$(MEMORY_DIR)

.PHONY = all
all: $(XMEM_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(XMEM_ALL): $(XMEM_DIRS) $(XMEM_COMMON_OBJ)
	$(LD) --relocatable -T $(XMEM_LDS) $(XMEM_MALLOC_OBJ) $(XMEM_COMMON_OBJ) -o $@

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
