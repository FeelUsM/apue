#define USE_ERR
#include "apue.h"
#define BUFFSIZE 4096
int
main(void)
{
	int n;
	char buf[BUFFSIZE];
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("ошибка записи");
	if (n < 0)
		err_sys("ошибка чтения");
	exit(0);
}