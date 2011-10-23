#include <stdio.h>
#include <string.h>

int main()
{
	char *pmsg = "hello, world!";

	/* result in Segmentation fault */
	strcpy(pmsg, "hi, there."); 
	printf("%s\n", pmsg);

	return 0;
}
