XSCHED_SOURCE_NAMES = idle

XSCHED_LDS     =  sched.lds
XSCHED_OBJ     := $(foreach OBJ, $(XSCHED_SOURCE_NAMES), $(OBJ).o)

XSCHED_INCLUDE := $(INCLUDE) \
				  -I$(SRC_ROOT)/kernel/sched

.PHONY = all
all: $(XSCHED_ALL)
	$(CP) $^ $(SRC_ROOT)/kernel

$(XSCHED_ALL): $(XSCHED_OBJ)
	$(LD) --relocatable -T $(XSCHED_LDS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(XSCHED_INCLUDE) -c $^ -o $@ 

CLEAN = *.o *.c.*

.PHONY += clean
clean:
	$(RM) $(CLEAN)
