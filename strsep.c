#include <string.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	char* const delim = ":";
	char mac[] = "00:1e:7c:27:e9:55";
	char *token, *cur = mac;

	printf("mac address: ");
	while ((token = strsep(&cur, delim)))
		printf("%s ", token);

	printf("\n");
	return 0;
}
