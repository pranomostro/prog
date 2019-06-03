#include <stdio.h>
#include <limits.h>

int main(void)
{
	printf("%d\n", INT_MAX);
	for(int i=0; i<INT_MAX; i++)
		;
	return 0;
}
