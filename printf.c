#include <stdio.h>

int main()
{
	int a = 7;
	char s[] = "uvc";

	printf("%i\n", a);
	printf("%.*s\n", (int)sizeof(s), s);

	printf("This is a printf test case, join "
			"two lines together\n");

	return 0;
}
