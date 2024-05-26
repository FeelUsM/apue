#define USE_ERR
#include "apue.h"
#include <fcntl.h>
int
main(void)
{
	if (open("tempfile", O_RDWR) < 0)
		err_sys("ошибка вызова функции open");
	if (unlink("tempfile") < 0)
		err_sys("ошибка вызова функции unlink");
	printf("файл удален\n");
	sleep(15);
	printf("конец\n");
	exit(0);
}
/*
$ ls -l tempfile посмотрим размер файла
-rw-r----- 1 sar 413265408 Jan 21 07:14 tempfile
$ df /home проверим объем доступного свободного пространства
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1956332 9065108 18% /home
$ ./a.out & запустим программу из листинга 4.5 как фоновый процесс
1364 командная оболочка вывела идентификатор процесса
$ файл удален файл отцеплен
ls -l tempfile проверим, остался ли файл на месте
ls: tempfile: No such file or directory запись из каталога была удалена
$ df /home проверим, освободилось ли дисковое пространство
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1956332 9065108 18% /home
$ конец программа завершилась, все файлы закрыты
df /home теперь должно освободиться пространство на диске
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1552352 9469088 15% /home
на диске освободилось 394,1 Mбайт
*/