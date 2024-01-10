DIRS = bus serial video

.PHONY = all
all: $(DIRS)

.PHONY += $(DIRS)
$(DIRS): check_obj_dir
	$(MAKE) -C $@

.PHONY += check_obj_dir
check_obj_dir: _force
	[[ -e obj ]] || mkdir obj

CLEAN_DIRS := $(foreach DIR, $(DIRS), $(addsuffix .clean,$(DIR)))

.PHONY += clean $(CLEAN_DIRS)
clean: $(CLEAN_DIRS)
	$(RM) -r obj

$(CLEAN_DIRS): _force
	$(MAKE) clean -C $(basename $@)

_force: ;
