#include "apue.h"
int
main(void)
{
	printf("привет от процесса с идентификатором %ld\n", (long)getpid());
	exit(0);
}