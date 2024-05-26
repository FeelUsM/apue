#define USE_ERR
#include "apue.h"
int
main(void)
{
	if (chdir("/tmp") < 0)
		err_sys("ошибка вызова функции chdir");
	printf("каталог /tmp стал текущим рабочим каталогом\n");
	exit(0);
}