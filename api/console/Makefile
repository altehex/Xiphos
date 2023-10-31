APIS =  xiphos_std_console
DIRS := $(foreach DIR, $(APIS), $(SRC_ROOT)/api/console/$(DIR))

.PHONY = all 
all: $(DIRS)

.PHONY += $(DIRS)
$(DIRS): _force
	$(MAKE) -C $@

CLEAN_DIRS := $(foreach DIR, $(DIRS), $(addsuffix .clean,$(DIR)))

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
