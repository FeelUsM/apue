#define USE_ERR
#include "apue.h"
#include <fcntl.h>
int
main(int argc, char *argv[])
{
	int i, fd;
	struct stat statbuf;
	struct timespec times[2];
	for (i = 1; i < argc; i++) {
		if (stat(argv[i], &statbuf) < 0) { /* получить значения времени */
			err_ret("%s: ошибка вызова функции stat", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* усечение */
			err_ret("%s: ошибка вызова функции open", argv[i]);
			continue;
		}
		times[0] = statbuf.st_atim;
		times[1] = statbuf.st_mtim;
		if (futimens(fd, times) < 0) /* установить значения времени */
			err_ret("%s: ошибка вызова функции futimens", argv[i]);
		close(fd);
	}
	exit(0);
}