#include <stdio.h>
#include <string.h>
#include <malloc.h>

void getmem(char **device)
{
	*device = "hello world!";
}

int main()
{
#if 0
	char dev_node[60];
#else
	char **dev_node;
	dev_node = (char **)malloc(60);
#endif
	memset(dev_node, '\0', sizeof(dev_node));
	getmem(dev_node);

	printf("the string is: %s\n", *dev_node);

	return 0;
}
