#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	printf("%d\n", getpid());
	for(int i=1; i<argc; i++)
		for(int j=0; j<strlen(argv[i]); j++)
			argv[i][j]='x';
	sleep(60);
	return 0;
}
