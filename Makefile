OBJS := and array foo ascii char memtest sizeofarray ifdef \
	sizeof typeof shift popcount string2hex zero_array \
	asprintf microsoft bit_complete gcc_optimise	   \
	comiler-specific max malloc0 endian odd_array      \
	volatile corcpp atexit swap helloworld nomain	   \
	printf weak bin2h inotify signal list		   \
	get_local_macaddr time cp strsep strtok bitfield

all : $(OBJS)

$(OBJS): $(OBJS:%=%.c)
	$(CC) -o $@ $(@:%=%.c) -Wall

clean:
	rm -f $(OBJS) *.s a.out
