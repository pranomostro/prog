#include <stdio.h>

int main(void)
{
	struct a{
		double a1;
		int* a2;
	} ai;
	struct b{
		int* b1;
		int b2;
	};

	struct b *bi;
	ai.a1=10;
	ai.a2=NULL;

	bi=(void*)&ai;

	printf("%p %d\n", bi->b1, bi->b2);

	return 0;
}
