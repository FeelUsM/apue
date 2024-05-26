#define USE_ERR
#include "apue.h"
int
main(void)
{
	char *ptr;
	size_t size;
	if (chdir("foo/testdir") < 0)
		err_sys("ошибка вызова функции chdir");
	ptr = path_alloc(&size); /* наша собственная функция */
	if (getcwd(ptr, size) == NULL)
		err_sys("ошибка вызова getcwd");
	printf("cwd = %s\n", ptr);
	exit(0);
}