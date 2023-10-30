API_NAME = xiphos_std_vesa_api
API_CATEGORY = video

XIPHOS_STD_VESA_API_SOURCE_NAMES = setup_vesa

XIPHOS_STD_VESA_API_OBJ = $(foreach OBJ, $(XIPHOS_STD_VESA_API_SOURCE_NAMES), \
						  $(OBJ).o)
XIPHOS_STD_VESA_API_LDS = xiphos_std_vesa_api.lds

INCLUDE += -I$(SRC_ROOT)/api/$(API_CATEGORY)/$(API_NAME)

.PHONY += _all
_all: $(XIPHOS_STD_VESA_API_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

$(foreach NAME, $(XIPHOS_STD_VESA_API_SOURCE_NAMES), \
	$(eval $(NAME).o: $(NAME).c))

CLEAN = *.o *.c.*

clean:
	$(RM) $(CLEAN)
