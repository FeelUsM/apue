#define USE_ERR
#include "apue.h"
#include <fcntl.h>
int
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("Использование: a.out <имя_файла>");

	if (access(argv[1], R_OK) < 0)
		err_ret("ошибка вызова функции access для файла %s", argv[1]);
	else
		printf("доступ для чтения разрешен\n");

	if (open(argv[1], O_RDONLY) < 0)
		err_ret("ошибка вызова функции open для файла %s", argv[1]);
	else
		printf("файл благополучно открыт для чтения\n");

	exit(0);
}
/*
$ ls -l a.out
-rwxrwxr-x 1 sar 15945 Nov 30 12:10 a.out
$ ./a.out a.out
Доступ для чтения разрешен
Файл благополучно открыт для чтения

$ ls -l /etc/shadow
-r-------- 1 root 1315 Jul 17 2002 /etc/shadow
$ ./a.out /etc/shadow
ошибка вызова функции access для файла /etc/shadow: Permission denied
ошибка вызова функции open для файла /etc/shadow: Permission denied

$ su получим права суперпользователя
Password: вводим пароль суперпользователя
# chown root a.out делаем суперпользователя владельцем файла
# chmod u+s a.out и устанавливаем бит set-user-ID
# ls -l a.out проверяем владельца файла и состояние бита SUID
-rwsrwxr-x 1 root 15945 Nov 30 12:10 a.out
# exit возвращаемся к правам обычного пользователя
$ ./a.out /etc/shadow
ошибка вызова функции access для файла /etc/shadow: Permission denied
файл благополучно открыт для чтения
*/