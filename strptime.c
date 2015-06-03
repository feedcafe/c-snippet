#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	struct tm tm;
	char buf[128];

	memset(&tm, 0, sizeof(struct tm));
	strptime("06/07/1988 11:06:07", "%m/%d/%Y %H:%M:%S", &tm);
	strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
	puts(buf);

	return 0;
}
