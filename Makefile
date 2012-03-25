OBJS := and array foo ascii char memtest sizeofarray ifdef \
	sizeof typeof shift popcount string2hex zero_array \
	asprintf microsoft bit_complete gcc_optimise	   \
	comiler-specific max malloc0

all : $(OBJS)

$(OBJS): $(OBJS:%=%.c)
	$(CC) -o $@ $(@:%=%.c) -Wall

clean:
	rm -f $(OBJS)
