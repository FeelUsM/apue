// L-2-3.c
#ifdef NAME_NAIN
#define USE_ERR
#endif
#include "apue.h"
#include <errno.h>
#include <limits.h>

#define XSTR(x) STR(x)
#define STR(x) #x
#ifdef PATH_MAX
	static long pathmax = PATH_MAX;
	//#pragma message "PATH_MAX = " XSTR(PATH_MAX) 
#else
	static long pathmax = 0;
	#pragma message "PATH_MAX not defined "
#endif
static long posix_version = 0;
static long xsi_version = 0;
/* Если константа PATH_MAX не определена */
/* адекватность следующего числа не гарантируется */
#define PATH_MAX_GUESS 1024

#define debug(...) printf(__VA_ARGS__)

char *
path_alloc(size_t *sizep) /* если удалось выделить память, */
{ /* возвращает также выделенной объем */
	char *ptr;
	size_t size;
	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);
	if (xsi_version == 0)
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	if (pathmax == 0) { /* первый вызов функции */
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
			if (errno == 0) {
				pathmax = PATH_MAX_GUESS; /* если константа не определена */
				err_msg("PATH_MAX не определён, используется значение %d",PATH_MAX_GUESS);
			}
			else {
				err_sys("ошибка вызова pathconf с параметром _PC_PATH_MAX");
			}
		} else {
			pathmax++; /* добавить 1, так как путь относительно корня */
		}
	}
	/*
	* До версии POSIX.1-2001 не гарантируется, что PATH_MAX включает
	* завершающий нулевой байт. То же для XPG3.
	*/
	if ((posix_version < 200112L) && (xsi_version < 4))
		size = pathmax + 1;
	else
		size = pathmax;
	//debug("path_alloc %lu\n",size);
	if ((ptr = malloc(size)) == NULL)
		err_sys("malloc error for pathname");
	if (sizep != NULL)
		*sizep = size;
	return(ptr);
}

#ifdef NAME_MAIN
int main() {
	path_alloc(NULL);
}
#endif