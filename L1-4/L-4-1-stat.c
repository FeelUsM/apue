#define USE_ERR
#include "apue.h"
int
main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	char *ptr;
	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			err_ret("ошибка вызова функции lstat");
			continue;
		}
		if (S_ISREG(buf.st_mode))
			ptr = "обычный файл";
		else if (S_ISDIR(buf.st_mode))
			ptr = "каталог";
		else if (S_ISCHR(buf.st_mode))
			ptr = "файл символьного устройства";
		else if (S_ISBLK(buf.st_mode))
			ptr = "файл блочного устройства";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "символическая ссылка";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "сокет";
		else
			ptr = "** неизвестный тип файла **";
		printf("%s\n", ptr);
	}
	exit(0);
}