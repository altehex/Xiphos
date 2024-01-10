DIRS = xiphos_std_pci_express

.PHONY = all 
all: $(DIRS)

.PHONY += $(DIRS)
$(DIRS): _force
	$(MAKE) -C $@
	$(CP) $@/$@.o $(SRC_ROOT)/libos/obj

CLEAN_DIRS := $(foreach DIR, $(DIRS), $(addsuffix .clean,$(DIR)))

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
