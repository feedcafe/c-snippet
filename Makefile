OBJS := and array foo ascii char memtest sizeofarray ifdef \
	sizeof typeof shift popcount string2hex zero_array \
	asprintf microsoft

all : $(OBJS)

$(OBJS): $(OBJS:%=%.c)
	$(CC) -o $@ $(@:%=%.c) -Wall

clean:
	rm -f $(OBJS)
