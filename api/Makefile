_DIRS = console
DIRS := $(foreach DIR,$(_DIRS),$(SRC_ROOT)/api/$(DIR))

.PHONY := all
all: $(DIRS)

.PHONY += $(DIRS)
$(DIRS): _force
	$(MAKE) -C $@

_force: ;

CLEAN_DIRS := $(foreach DIR, $(DIRS),$(addsuffix .clean,$(DIR)))

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)

$(CLEAN_DIRS):
	$(MAKE) clean -C $(basename $@)
