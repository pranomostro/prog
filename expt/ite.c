#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	setbuf(stdout, NULL);
	printf("a");
	sleep(1);
	printf("b");
	sleep(1);
	printf("\33[2K\r");
	sleep(1);
	printf("ef");
	sleep(1);
	printf("c\n");
	return 0;
}
