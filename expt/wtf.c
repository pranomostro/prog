#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint32_t val;
	for(val=0; val<=UINT32_MAX; val++)
		printf("%d %.24f\n", val, (float)val);

	return 0;
}
