export PWD = \
	$(shell pwd)

# 1: source names list
export OBJ_WRAP = $(foreach OBJ, $(1), $(OBJ).o)

# 1: directory list (relative)
export INCLUDE_WRAP = \
	$(foreach INC, $(1), -I$(INC))

# 1: directory list
# 2: prefix
export PREFIX_INCLUDE_WRAP = \
	$(foreach INC, $(foreach DIR, $(1), $(addprefix $(2)/, $(1))), -I$(INC))
