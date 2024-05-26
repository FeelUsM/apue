#define USE_ERR
#include "apue.h"
int
main(void)
{
	int c;
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("ошибка вывода");
	if (ferror(stdin))
		err_sys("ошибка ввода");
	exit(0);
}