#define USE_ERR
#include "apue.h"
#include <fcntl.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int
main(void)
{
	printf("S_IRUSR = %o\n",S_IRUSR);
	printf("S_IWUSR = %o\n",S_IWUSR);
	printf("S_IXUSR = %o\n",S_IXUSR);

	printf("S_IRGRP = %o\n",S_IRGRP);
	printf("S_IWGRP = %o\n",S_IWGRP);
	printf("S_IXGRP = %o\n",S_IXGRP);

	printf("S_IROTH = %o\n",S_IROTH);
	printf("S_IWOTH = %o\n",S_IWOTH);
	printf("S_IXOTH = %o\n",S_IXOTH);

	printf("S_ISUID = %o\n",S_ISUID);
	printf("S_ISGID = %o\n",S_ISGID);
	printf("S_ISVTX = %o\n",S_ISVTX);

	if (creat("baz1", RWRWRW) < 0)
		err_sys("ошибка вызова функции creat для файла baz1");

	if (creat("baz2", RWRWRW^RWRWRW/*0*/) < 0)
		err_ret("ошибка вызова функции creat для файла baz2");

	mode_t m = umask(0);
	printf("RWRWRW   mode is %o\n",RWRWRW);
	printf("previous mode is %o\n",m);
	if (creat("foo", RWRWRW) < 0)
		err_sys("ошибка вызова функции creat для файла foo");

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
		err_sys("ошибка вызова функции creat для файла bar");

	exit(0);
}