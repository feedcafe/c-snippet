#include <stdio.h>

#define	ARRAY_SIZE(a)	sizeof(a) / sizeof(a[0])

int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};

	printf("size of array is: %d\n", ARRAY_SIZE(a));

	return 0;
}
