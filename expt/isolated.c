#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "findtest.h"

int main(void)
{
	uint32_t key;
	size_t i, n, inc=16, len=268435456;
	uint32_t* data=calloc(len, sizeof(uint32_t));

	for(n=rand()%inc, i=0; i<len; i++, n+=rand()%inc)
		data[i]=n;

	for(i=0; i<4096; i++)
	{
		key=rand()%(len*inc);
		ifind1(key, data, len);
	}

	return 0;
}
