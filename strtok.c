#include <string.h> 
#include <stdio.h>

int main(void)
{
	char str[] = "The quick brown fox jumps over the lazy dog";
	char *p = NULL;
	const char *delim = " ";

	printf("A phrase that contains all of the letters of the alphabet:\n%s\n", str);

	p = strtok(str, delim);
	while (p != NULL) {
		printf("%s\n", p);
		p = strtok(NULL, delim);
	} 

	return 0;
}
