#include <errno.h> /* определение переменной errno */
#include <stdarg.h> /* список аргументов переменной длины ISO C */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 200
/*
* Выводит сообщение и возвращает управление в вызывающую функцию.
* Вызывающая функция определяет значение флага "errnoflag".
*/
static inline void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s\n", strerror(error));
	fflush(stdout); /* в случае, когда stdout и stderr - одно и то же устройство */
	fputs(buf, stderr);
	fflush(NULL); /* сбрасывает все выходные потоки */
}

// err_msg                           Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
// err_perr  errno                   Обрабатывает нефатальные ошибки,    связанные с системными вызовами.
// err_quit                 exit(1); Обрабатывает   фатальные ошибки, не связанные с системными вызовами.
// err_sys   errno          exit(1); Обрабатывает   фатальные ошибки,    связанные с системными вызовами.
// err_dump  errno          abort(); Обрабатывает   фатальные ошибки,    связанные с системными вызовами.

// err_cont Явный параметр          Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
// err_exit Явный параметр exit(1); Обрабатывает   фатальные ошибки, не связанные с системными вызовами.


/*
* Обрабатывает нефатальные ошибки, связанные с системными вызовами.
* Выводит сообщение и возвращает управление.
*/
static inline void
err_perr(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
static inline void
err_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	exit(1);
}
/*
* Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
* Код ошибки передается в аргументе.
* Выводит сообщение и возвращает управление.
*/
static inline void
err_cont(int error, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, не связанные с системными вызовами.
* Код ошибки передается в аргументе.
* Выводит сообщение и завершает работу процесса.
*/
static inline void
err_exit(int error, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
	exit(1);
}
/*
* Обрабатывает фатальные ошибки, связанные с системными вызовами.
* Выводит сообщение, создает файл core и завершает работу процесса.
*/
static inline void
err_dump(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	abort(); /* записать дамп памяти в файл и завершить процесс */
	exit(1); /* этот вызов никогда не должен выполниться */
}

/*
* Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
* Выводит сообщение и возвращает управление.
*/
static inline void
err_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, не связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
static inline void
err_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}
