//#include "apue.h"
#include <stdio.h>//fprintf(), stderr
#include <string.h> // strerror()
#include <errno.h>//errno
#include <stdlib.h>//exit()
int
main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}