#define USE_ERR
#include "apue.h"
int
main(void)
{
	struct stat statbuf;
	/* включить бит set-group-ID и выключить group-execute */
	if (stat("foo", &statbuf) < 0)
		err_sys("ошибка вызова функции stat для файла foo");
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("ошибка вызова функции chmod для файла foo");
	/* установить режим в значение "rw-r--r--" */
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		err_sys("ошибка вызова функции chmod для файла bar");
	exit(0);
}