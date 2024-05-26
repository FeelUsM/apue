//gcc L-4-7-myftw.c path_alloc.c
#define USE_ERR
#include "apue.h"
#include <dirent.h>
#include <limits.h>

#define debug(...) //printf(__VA_ARGS__)

/* тип функции, которая будет вызываться для каждого встреченного файла */
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *, int);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int
main(int argc, char *argv[])
{
	int ret;
	if (argc != 2)
		err_quit("Использование: ftw <начальный_каталог>");

	ret = myftw(argv[1], myfunc); /* выполняет всю работу */

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

	if (ntot == 0)
		ntot = 1;/* во избежание деления на 0 вывести 0 для всех счетчиков */

	printf("обычные файлы                          = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
	printf("каталоги                               = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
	printf("специальные файлы блочных устройств    = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
	printf("специальные файлы символьных устройств = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
	printf("FIFO                                   = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("символические ссылки                   = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
	printf("сокеты                                 = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);

	exit(ret);
}

/*
* Выполняет обход дерева каталогов, начиная с каталога "pathname".
* Для каждого встреченного файла вызывает пользовательскую функцию func().
*/
#define FTW_F 1 /* file, файл, не являющийся каталогом */
#define FTW_D 2 /* dir, каталог */
#define FTW_DNR 3 /* dir not reachable, каталог, который недоступен для чтения */
#define FTW_NS 4 /* no stat, файл, информацию о котором невозможно получить с помощью stat */

static char *fullpath; /* полный путь к каждому из файлов */
static size_t pathlen;
static size_t maxdepth;

static int /* возвращает то, что вернула функция func() */
myftw(char *pathname, Myfunc *func)
{
	// &len -> &pathlen - опасная опечатка
	fullpath = path_alloc(&pathlen); /* выделить память для PATH_MAX+1 байт */
	/* (листинг 2.3) */
	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("ошибка вызова realloc");
	}
	strcpy(fullpath, pathname);
	maxdepth = 0;
	int tmp = dopath(func,1);
	printf("\n");// after printf("%lu ",maxdepth);
	free(fullpath);
	return tmp;
}

/*
* Выполняет обход дерева каталогов, начиная с "fullpath".
* Если "fullpath" не является каталогом, для него вызывается lstat(),
* func() и затем выполняется возврат.
* Для каталогов производится рекурсивный вызов функции.
*/
static int /* возвращает то, что вернула функция func() */
dopath(Myfunc* func, int depth)
{
	if(depth > maxdepth) {
		maxdepth = depth;
		printf("%lu ",maxdepth);
	}
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret, n;

	if (lstat(fullpath, &statbuf) < 0) 
		return(func(fullpath, &statbuf, FTW_NS)); /* ошибка вызова функции stat */ 
	if (S_ISDIR(statbuf.st_mode) == 0)
		return(func(fullpath, &statbuf, FTW_F));  /* не каталог */
	/*
	* Это каталог. Сначала вызвать функцию func(),
	* а затем обработать все файлы в этом каталоге.
	*/
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return(ret);
	n = strlen(fullpath);
	if (n + NAME_MAX + 2 > pathlen) { /* увеличить размер буфера */
		debug("do realloc %lu\n",pathlen);
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("ошибка вызова realloc");
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;
	if ((dp = opendir(fullpath)) == NULL) // !!!!!!! макс. глубина рекурсии ограничена макс. кол-вом открытых файлов-каталогов на процесс
		return(func(fullpath, &statbuf, FTW_DNR));/* каталог недоступен */
	//printf("%d-%ld ",depth,-telldir(dp));
	while ((dirp = readdir(dp)) != NULL) {
		//printf("%d-%ld ",depth,-telldir(dp));
		if (strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0)
		continue; /* пропустить каталоги "." и ".." */
		strcpy(&fullpath[n], dirp->d_name); /* добавить имя после слеша */
		if ((ret = dopath(func,depth+1)) != 0) /* рекурсия */
			break; /* выход по ошибке */
	}
	//printf("%d-%ld ",depth,-telldir(dp));
	fullpath[n-1] = 0; /* стереть часть строки от слеша и до конца */
	if (closedir(dp) < 0)
		err_ret("невозможно закрыть каталог %s", fullpath);
	return(ret);
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
	debug("%s\n",pathname);
	switch (type) {
	case FTW_F:
		switch (statptr->st_mode & S_IFMT) {
		case S_IFREG: nreg++; break;
		case S_IFBLK: nblk++; break;
		case S_IFCHR: nchr++; break;
		case S_IFIFO: nfifo++; break;
		case S_IFLNK: nslink++; break;
		case S_IFSOCK: nsock++; break;
		case S_IFDIR: /* каталоги должны иметь type = FTW_D*/
			err_dump("признак S_IFDIR для %s", pathname);
		}
	break;
	case FTW_D:
		ndir++;
	break;
	case FTW_DNR:
		err_ret("закрыт доступ к каталогу %s", pathname);
	break;
	case FTW_NS:
		err_ret("ошибка вызова функции stat для %s", pathname);
	break;
	default:
		err_dump("неизвестный тип %d для файла %s", type, pathname);
	}
	return(0);
}