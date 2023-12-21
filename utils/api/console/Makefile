APIS =  xiphos_std_console

.PHONY = all 
all: $(APIS)

.PHONY += $(APIS)
$(APIS): _force
	$(MAKE) -C $@
	$(CP) $@/$@.o $(SRC_ROOT)/api/obj

CLEAN_DIRS := $(foreach DIR, $(APIS), $(addsuffix .clean,$(DIR)))

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
