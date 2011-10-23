#include <stdio.h>
#include <string.h>

int main()
{
	char pmsg[] = "hello, world!";

	strcpy(pmsg, "hi, there."); 
	printf("%s\n", pmsg);

	return 0;
}
