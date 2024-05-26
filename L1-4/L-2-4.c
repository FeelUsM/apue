#define USE_ERR
#include "apue.h"
#include <errno.h>
#include <limits.h>
#ifdef OPEN_MAX
	static long openmax = OPEN_MAX;
#else
	static long openmax = 0;
#endif
/*
* Если константа PATH_MAX не определена 
* адекватность следующего числа не гарантируется
*/
#define OPEN_MAX_GUESS 256
long
open_max(void)
{
	if (openmax == 0) { /* первый вызов функции */
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
			if (errno == 0)
				openmax = OPEN_MAX_GUESS; /* неопределенный предел */
			else
				err_sys("ошибка вызова sysconf с параметром _SC_OPEN_MAX");
		}
	}
	return(openmax);
}
int main() {
	open_max();
}