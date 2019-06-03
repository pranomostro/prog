#include <stdlib.h>
#include <stdio.h>

int* f(void)
{
	int a=5;
	return &a;
}

int main(void)
{
	int* a;
	a=f();
	printf("%d\n", *a);
	return 0;
}
