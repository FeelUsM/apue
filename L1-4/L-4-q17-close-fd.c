#define USE_ERR
#include "apue.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	const char * path = "/dev/fd/1";
	unlink(path);
	int fd;
	if ((fd = creat(path, FILE_MODE)) < 0)
		err_sys("...");
}