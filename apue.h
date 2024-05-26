/*
* Наш заголовочный файл, который подключается перед любыми
* стандартными системными заголовочными файлами
*/
#ifndef _APUE_H
#define _APUE_H
#define _POSIX_C_SOURCE 200809L
#if defined(SOLARIS) /* Solaris 10 */
#	define _XOPEN_SOURCE 600
#else
#	define _XOPEN_SOURCE 700
#endif

#include <sys/types.h> /* некоторые системы требуют этого заголовка */
#include <sys/stat.h>
#include <sys/termios.h> /* структура winsize */
#if defined(MACOS) || !defined(TIOCGWINSZ)
#	include <sys/ioctl.h>
#endif
#include <stdio.h> /* для удобства */
#include <stdlib.h> /* для удобства */
#include <stddef.h> /* макрос offsetof */
#include <string.h> /* для удобства */
#include <unistd.h> /* для удобства */
#include <signal.h> /* константа SIG_ERR */

#define MAXLINE 4096 /* максимальная длина строки */
/*
* Права доступа по умолчанию к создаваемым файлам.
*/
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
/*
* Права доступа по умолчанию к создаваемым каталогам.
*/
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
typedef void Sigfunc(int); /* обработчики сигналов */
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
/*
* Прототипы наших собственных функций.
*/
char *   path_alloc(size_t *);              /* листинг 2.3 */
long     open_max(void);                    /* листинг 2.4 */
int      set_cloexec(int);                  /* листинг 13.5 */
void     clr_fl(int, int);                  
void     set_fl(int, int);                  /* листинг 3.5 */
void     pr_exit(int);                      /* листинг 8.5 */
void     pr_mask(const char *);             /* листинг 10.10 */
Sigfunc *signal_intr(int, Sigfunc *);       /* листинг 10.12 */
void     daemonize(const char *);           /* листинг 13.1 */
void     sleep_us(unsigned int);            /* упражнение 14.5 */
ssize_t  readn(int, void *, size_t);        /* листинг 14.9 */
ssize_t  writen(int, const void *, size_t); /* листинг 14.9 */
int      fd_pipe(int *);                    /* листинг 17.1 */
int      recv_fd(int, ssize_t (*func)(int,const void *, size_t)); /* листинг 17.10 */
int      send_fd(int, int);                  /* листинг 17.9 */
int      send_err(int, int, const char *);   /* листинг 17.8 */
int      serv_listen(const char *);          /* листинг 17.5 */
int      serv_accept(int, uid_t *);          /* листинг 17.6 */
int      cli_conn(const char *);             /* листинг 17.7 */
int      buf_args(char *, int (*func)(int, char **)); /* листинг 17.19 */
int      tty_cbreak(int);                    /* листинг 18.10 */
int      tty_raw(int);                       /* листинг 18.10 */
int      tty_reset(int);                     /* листинг 18.10 */
void     tty_atexit(void);                   /* листинг 18.10 */
struct termios *
         tty_termios(void);                  /* листинг 18.10 */
int      ptym_open(char *, int);             /* листинг 19.1 */
int      ptys_open(char *);                  /* листинг 19.1 */
#ifdef TIOCGWINSZ
	pid_t pty_fork(int *, char *, int, const struct termios *, const struct winsize *); /* листинг 19.2 */
#endif
int     lock_reg(int, int, int, off_t, int, off_t); /* листинг 14.2 */
#define   read_lock(fd, offset, whence, len) lock_reg((fd), F_SETLK,  F_RDLCK, (offset), (whence), (len))
#define  readw_lock(fd, offset, whence, len) lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define  write_lock(fd, offset, whence, len) lock_reg((fd), F_SETLK,  F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define     un_lock(fd, offset, whence, len) lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))
pid_t lock_test(int, int, off_t, int, off_t); /* листинг 14.3 */
#define is_read_lockable(fd, offset, whence, len) (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len) (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)
                                                                 // Функция  Добавляет строку от strerror? Аргументы для strerror Завершает процесс?
void err_ret (     const char *, ...);                           // err_ret  Да                            errno                  return;
void err_sys (     const char *, ...) __attribute__((noreturn)); // err_sys  Да                            errno                  exit(1);
void err_cont(int, const char *, ...);                           // err_ret  Да                            Явный параметр         return;
void err_exit(int, const char *, ...) __attribute__((noreturn)); // err_exit Да                            Явный параметр         exit(1);
void err_dump(     const char *, ...) __attribute__((noreturn)); // err_dump Да                            errno                  abort();
void err_msg (     const char *, ...); /* приложение B */        // err_msg  Нет                                                  return;
void err_quit(     const char *, ...) __attribute__((noreturn)); // err_quit Нет                                                  exit(1);

void log_open(     const char *, int, int);                      
void log_ret (     const char *, ...);                           // log_ret  Да                            errno                  return;
void log_sys (     const char *, ...) __attribute__((noreturn)); // log_sys  Да                            errno                  exit(2);
void log_exit(int, const char *, ...) __attribute__((noreturn)); 
void log_msg (     const char *, ...); /* приложение B */        // log_msg  Нет                                                  return;
void log_quit(     const char *, ...) __attribute__((noreturn)); // log_quit Нет                                                  exit(2);

void TELL_WAIT(void); /* предок/потомок из раздела 8.9 */
void TELL_PARENT(pid_t);
void TELL_CHILD(pid_t);
void WAIT_PARENT(void);
void WAIT_CHILD(void);

//------------------------------------------------------------------------------
#ifdef USE_ERR

#include <errno.h> /* определение переменной errno */
#include <stdarg.h> /* список аргументов переменной длины ISO C */
static void err_doit(int, int, const char *, va_list);
/*
* Обрабатывает нефатальные ошибки, связанные с системными вызовами.
* Выводит сообщение и возвращает управление.
*/
void
err_ret(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
void
err_sys(const char *fmt, ...) {
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
void
err_cont(int error, const char *fmt, ...) {
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
void
err_exit(int error, const char *fmt, ...) {
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
void
err_dump(const char *fmt, ...) {
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
void
err_msg(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, не связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
void
err_quit(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}
/*
* Выводит сообщение и возвращает управление в вызывающую функцию.
* Вызывающая функция определяет значение флага "errnoflag".
*/
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	strcat(buf, "\n");
	fflush(stdout); /* в случае, когда stdout и stderr - одно и то же устройство */
	fputs(buf, stderr);
	fflush(NULL); /* сбрасывает все выходные потоки */
}
#endif // USE_ERR
//------------------------------------------------------------------------------
#ifdef USE_LOG

/*
* Процедуры обработки ошибок для программ, которые могут работать как демоны.
*/
#include "apue.h"
#include <errno.h> /* определение переменной errno */
#include <stdarg.h> /* список аргументов переменной длины ISO C */
#include <syslog.h>
static void log_doit(int, int, int, const char *, va_list ap);
/*
* В вызывающем процессе должна быть определена и установлена эта переменная:
* ненулевое значение - для интерактивных программ, нулевое – для демонов
*/
extern int log_to_stderr;
/*
* Инициализировать syslog(), если процесс работает в режиме демона.
*/
void
log_open(const char *ident, int option, int facility)
{
	if (log_to_stderr == 0)
		openlog(ident, option, facility);
}
/*
* Обрабатывает нефатальные ошибки, связанные с системными вызовами.
* Выводит сообщение, соответствующее содержимому переменной errno,
* и возвращает управление.
*/
void
log_ret(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
void
log_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}
/*
* Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
* Выводит сообщение и возвращает управление.
*/
void
log_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
}
/*
* Обрабатывает фатальные ошибки, не связанные с системными вызовами.
* Выводит сообщение и завершает работу процесса.
*/
void
log_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}
/*
* Обрабатывает фатальные ошибки, связанные с системными вызовами.
* Номер ошибки передается в параметре.
* Выводит сообщение и завершает работу процесса.
*/
void
log_exit(int error, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	log_doit(1, error, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}
/*
* Выводит сообщение и возвращает управление в вызывающую функцию.
* Вызывающая функция должна определить значения аргументов
* "errnoflag" и "priority".
*/
static void
log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	strcat(buf, "\n");
	if (log_to_stderr) {
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	} else {
		syslog(priority, "%s", buf);
	}
}

#endif // USE_LOG



#endif /* _APUE_H */