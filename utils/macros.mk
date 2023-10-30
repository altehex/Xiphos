
# Can't get this to work
define CLEAN
	$(foreach DIR, $(1), $(eval $(MAKE) clean -C $(DIR)))
endef


# define GENERATE_TARGTETS_O_C =

# endef
