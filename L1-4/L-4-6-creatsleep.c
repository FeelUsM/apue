#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd = creat("file1", S_IRWXU|S_IRWXG);
	system("sleep 10");
	write(fd,"qwer",4);
	close(fd);

}