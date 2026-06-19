/*
запуск:
pty [опции] prog arg1 arg2
запускает prog arg1 arg2 в отдельном сеансе и псевдотерминале
(но другая сторона псевдотерминала подключается к текущему терминалу)

опции
		case 'd': /* драйвер для stdin/stdout 
		case 'e': /* отключить эхо-вывод для ведомого pty 
		case 'i': /* игнорировать символ EOF для стандартного ввода 
		case 'n': /* неинтерактивный режим 
		case 'v': /* вывод подробных сообщений 

один из сценариев использования:
pty [опции] prog arg1 arg2 | tee out.log # аналог программы scipt

*/


//#include "apue.h"
#	define _XOPEN_SOURCE 700

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#if defined(SOLARIS)
#	include <stropts.h>
#endif
#include <stdarg.h>
#include <sys/socket.h>

#define MAXLINE 4096 /* максимальная длина строки */
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

ssize_t /* Записывает n байт в дескриптор */
writen(int fd, const void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return(-1);/* ошибка, вернуть -1 */
			else
				break; /* ошибка, вернуть количество записанных байтов */
		} else if (nwritten == 0) {
			break;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return(n - nleft); /* возвращаемое значение >= 0 */
}

int
fd_pipe(int fd[2])
{
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}

typedef void Sigfunc(int);
Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
///////////////////////////////////////////////////////////////////////////
static enum { RESET, RAW, CBREAK } ttystate = RESET;
static struct termios save_termios;
static int ttysavefd = -1;

int
tty_raw(int fd) /* переводит терминал в режим прозрачного ввода (raw) */
{
	int err;
	struct termios buf;

	if (ttystate != RESET) {
		errno = EINVAL;
		return(-1);
	}
	if (tcgetattr(fd, &buf) < 0)
		return(-1);
	save_termios = buf; /* копия структуры */
	/*
	* Отключить эхо-вывод, выйти из канонического режима, отключить расширенную
	* обработку ввода, отключить обработку символов, генерирующих сигналы.
	*/
	buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	/*
	* Не выдавать сигнал SIGINT по псевдосимволу BREAK, отключить
	* преобразование CR->NL, отключить проверку паритета ввода,
	* не сбрасывать 8-й бит, отключить управление выводом.
	*/
	buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	/*
	* Сбросить маску управления размером, отключить контроль четности.
	*/
	buf.c_cflag &= ~(CSIZE | PARENB);
	/*
	* Установить размер символа 8 бит/символ.
	*/
	buf.c_cflag |= CS8;
	/*
	* Отключить обработку вывода.
	*/
	buf.c_oflag &= ~(OPOST);
	/*
	* Случай Б: минимум 1 байт, время ожидания не ограничено.
	*/
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);
	/*
	* Убедиться, что были произведены все изменения. Функция tcsetattr может
	* вернуть 0, даже если выполнена лишь часть изменений.
	*/
	if (tcgetattr(fd, &buf) < 0) {
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return(-1);
	}
	if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) ||
		(buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
		(buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 ||
		(buf.c_oflag & OPOST) || buf.c_cc[VMIN] != 1 ||
		buf.c_cc[VTIME] != 0
	) {
	/*
	* Были произведены лишь некоторые изменения.
	* Восстановить начальные настройки.
	*/
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return(-1);
	}
	ttystate = RAW;
	ttysavefd = fd;
	return(0);
}
int
tty_reset(int fd) /* восстанавливает состояние терминала */
{
	if (ttystate == RESET)
		return(0);
	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	ttystate = RESET;
		return(0);
}
void
tty_atexit(void) /* может устанавливаться вызовом atexit(tty_atexit) */
{
	if (ttysavefd >= 0)
		tty_reset(ttysavefd);
}

///////////////////////////////////////////////////////////////////////////

int
ptym_open(char *pts_name, int pts_namesz)
{
	char *ptr;
	int fdm, err;
	if ((fdm = posix_openpt(O_RDWR)) < 0)
		return(-1);
	if (grantpt(fdm) < 0) /* разрешить доступ к ведомому */
		goto errout;
	if (unlockpt(fdm) < 0) /* сбросить флаг блокировки ведомого */
		goto errout;
	if ((ptr = ptsname(fdm)) == NULL) /* получить имя ведомого */
		goto errout;
	/*
	* Вернуть имя ведомого устройства.
	* Завершить нулевым символом, чтобы обработать ситуацию, когда
	* strlen(ptr) > pts_namesz.
	*/
	strncpy(pts_name, ptr, pts_namesz);
	pts_name[pts_namesz - 1] = '\0';
	return(fdm); /* вернуть дескриптор ведущего */
errout:
	err = errno;
	close(fdm);
	errno = err;
	return(-1);
}

int
ptys_open(char *pts_name)
{
	int fds;
#if defined(SOLARIS)
	int err, setup;
#endif
	if ((fds = open(pts_name, O_RDWR)) < 0)
		return(-1);
#if defined(SOLARIS)
	/*
	* Проверить: возможно, поток уже настроен должным образом
	* благодаря автоматической вставке модулей.
	*/
	if ((setup = ioctl(fds, I_FIND, "ldterm")) < 0)
		goto errout;
	if (setup == 0) {
		if (ioctl(fds, I_PUSH, "ptem") < 0)
			goto errout;
		if (ioctl(fds, I_PUSH, "ldterm") < 0)
			goto errout;
		if (ioctl(fds, I_PUSH, "ttcompat") < 0) {
	errout:
			err = errno;
			close(fds);
			errno = err;
			return(-1);
		}
	}
#endif
	return(fds);
}

pid_t
pty_fork(int *ptrfdm, char *slave_name, int slave_namesz,
	const struct termios *slave_termios,
	const struct winsize *slave_winsize)
{
	int fdm, fds;
	pid_t pid;
	char pts_name[20];

	if ((fdm = ptym_open(pts_name, sizeof(pts_name))) < 0)
		err_sys("невозможно открыть ведущий pty: %s, ошибка %d", pts_name, fdm);
	if (slave_name != NULL) {
		/*
		* Вернуть имя ведомого устройства.
		* Завершить нулевым символом, чтобы обработать ситуацию, когда
		* strlen(ptr) > pts_namesz.
		*/
		strncpy(slave_name, pts_name, slave_namesz);
		slave_name[slave_namesz - 1] = '\0';
	}
	if ((pid = fork()) < 0) {
		return(-1);
	} else if (pid == 0) { /* дочерний процесс */
		if (setsid() < 0)
			err_sys("ошибка вызова функции setsid");
		/*
		* System V автоматически назначает управляющий терминал при открытии.
		*/
		if ((fds = ptys_open(pts_name)) < 0)
			err_sys("невозможно открыть ведомый pty");
		close(fdm); /* работа с ведущим pty в дочернем процессе завершена */
#if defined(BSD)
		/*
		* Команда TIOCSCTTY – способ назначения управляющего терминала в BSD.
		*/
		if (ioctl(fds, TIOCSCTTY, (char *)0) < 0)
			err_sys("ошибка выполнения команды TIOCSCTTY");
#endif
		/*
		* Инициализировать структуры termios и winsize ведомого pty.
		*/
		if (slave_termios != NULL) {
			if (tcsetattr(fds, TCSANOW, slave_termios) < 0)
				err_sys("ошибка вызова tcsetattr для ведомого pty");
		}
		if (slave_winsize != NULL) {
			if (ioctl(fds, TIOCSWINSZ, slave_winsize) < 0)
				err_sys("ошибка выполнения TIOCSWINSZ для ведомого pty");
		}
		/*
		* Связать stdin/stdout/stderr с терминалом в дочернем процессе.
		*/
		if (dup2(fds, STDIN_FILENO) != STDIN_FILENO)
			err_sys("ошибка вызова функции dup2 для stdin");
		if (dup2(fds, STDOUT_FILENO) != STDOUT_FILENO)
			err_sys("ошибка вызова функции dup2 для stdout");
		if (dup2(fds, STDERR_FILENO) != STDERR_FILENO)
			err_sys("ошибка вызова функции dup2 для stderr");
		if (fds != STDIN_FILENO && fds != STDOUT_FILENO &&
			fds != STDERR_FILENO)
		close(fds);
		return(0); /* вернуть 0 дочернему процессу, как это делает fork() */
	} else {
		/* родительский процесс */
		*ptrfdm = fdm; /* вернуть fd ведущего pty */
		return(pid); /* вернуть pid дочернего процесса родителю */
	}
}

#ifdef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

static void set_noecho(int); /* реализация находится в конце этого файла */
void do_driver(char *); /* в файле driver.c */
void loop(int, int); /* в файле loop.c */

int
main(int argc, char *argv[])
{
	int fdm, c, ignoreeof, interactive, noecho, verbose;
	pid_t pid;
	char *driver;
	char slave_name[20];
	struct termios orig_termios;
	struct winsize size;

	interactive = isatty(STDIN_FILENO);
	ignoreeof = 0;
	noecho = 0;
	verbose = 0;
	driver = NULL;
	opterr = 0; /* нежелательно, чтобы getopt() выводила на stderr */

	while ((c = getopt(argc, argv, OPTSTR)) != EOF) {
		switch (c) {
		case 'd': /* драйвер для stdin/stdout */
			driver = optarg;
		break;
		case 'e': /* отключить эхо-вывод для ведомого pty */
			noecho = 1;
		break;
		case 'i': /* игнорировать символ EOF для стандартного ввода */
			ignoreeof = 1;
		break;
		case 'n': /* неинтерактивный режим */
			interactive = 0;
		break;
		case 'v': /* вывод подробных сообщений */
			verbose = 1;
		break;
		case '?':
			err_quit("недопустимая опция: -%c\n", optopt);
		}
	}
	if (optind >= argc){
		err_quit("Использование: pty [ -d driver -einv ] program [ arg ... ]");
	}
	if (interactive) { /* получить текущие termios и winsize */
		if (tcgetattr(STDIN_FILENO, &orig_termios) < 0)
			err_sys("ошибка вызова функции tcgetattr для stdin");
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *) &size) < 0)
			err_sys("ошибка выполнения команды TIOCGWINSZ");
		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), &orig_termios, &size);
	} else {
		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), NULL, NULL);
	}
	if (pid < 0) {
		err_sys("ошибка вызова функции fork");
	} else if (pid == 0) { /* дочерний процесс */
		if (noecho)
			set_noecho(STDIN_FILENO); /* stdin – ведомый pty */
		if (execvp(argv[optind], &argv[optind]) < 0){
			err_sys("невозможно запустить: %s",argv[optind]);
		}
	}
	if (verbose) {
		fprintf(stderr, "имя ведомого = %s\n", slave_name);
		if (driver != NULL)
			fprintf(stderr, "драйвер = %s\n", driver);
	}
	if (interactive && driver == NULL) {
		if (tty_raw(STDIN_FILENO) < 0) /* перевести tty в прозрачный режим */
			err_sys("ошибка вызова функции tty_raw");
		if (atexit(tty_atexit) < 0) /* восстановление настроек при выходе */
			err_sys("ошибка вызова функции atexit");
	}
	if (driver)
		do_driver(driver); /* изменить наши stdin/stdout */
	loop(fdm, ignoreeof); /* копировать stdin -> ptym, ptym -> stdout */
	exit(0);
}

static void
set_noecho(int fd) /* отключить эхо-вывод (для ведомого pty) */
{
	struct termios stermios;
	if (tcgetattr(fd, &stermios) < 0)
	err_sys("ошибка вызова функции tcgetattr");
	stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	/*
	* Кроме того, отключить преобразование NL в CR/NL при выводе.
	*/
	stermios.c_oflag &= ~(ONLCR);
	if (tcsetattr(fd, TCSANOW, &stermios) < 0)
		err_sys("ошибка вызова функции tcsetattr");
}

#define BUFFSIZE 512
static void sig_term(int);
static volatile sig_atomic_t sigcaught; /* изменяется обработчиком сигнала */

void
loop(int ptym, int ignoreeof)
{
	pid_t child;
	int nread;
	char buf[BUFFSIZE];

	if ((child = fork()) < 0) {
		err_sys("ошибка вызова функции fork");
	} else if (child == 0) { /* дочерний процесс копирует stdin в ptym */
	for ( ; ; ) {
		if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0)
			err_sys("ошибка чтения из stdin");
		else if (nread == 0)
			break; /* EOF в stdin означает конец ввода */
		if (writen(ptym, buf, nread) != nread)
			err_sys("ошибка записи в ведущий pty");
	}
	/*
	* Мы всегда завершаем работу, когда обнаруживаем EOF в stdin,
	* но извещаем родителя только тогда, когда ignoreeof == 0.
	*/
	if (ignoreeof == 0)
		kill(getppid(), SIGTERM); /* известить родительский процесс */
		exit(0); /* и завершить работу; дочерний процесс */
		/* не может вернуть управление */
	}
	/*
	* Родительский процесс копирует ptym в stdout.
	*/
	if (signal_intr(SIGTERM, sig_term) == SIG_ERR)
		err_sys("ошибка вызова функции signal_intr для SIGTERM");
	for ( ; ; ) {
		if ((nread = read(ptym, buf, BUFFSIZE)) <= 0)
			break; /* перехвачен сигнал, ошибка или получен EOF */
		if (writen(STDOUT_FILENO, buf, nread) != nread)
			err_sys("ошибка записи в stdout");
	}
	/*
	* В этой точке мы оказываемся в трех случаях: функция sig_term()
	* (ниже) перехватила сигнал SIGTERM от дочернего процесса,
	* был прочитан символ EOF из ведущего pty (это означает,
	* что мы должны известить об этом потомка) или в случае ошибки.
	*/
	if (sigcaught == 0)
		/* послать сигнал потомку, */
		kill(child, SIGTERM); /* если от него не был получен сигнал */
	/*
	* Родительский процесс возвращает управление вызывающему.
	826 Глава 19. Псевдотерминалы
	*/
}
/*
* Потомок посылает сигнал SIGTERM, когда получает EOF из ведомого pty или
* когда функция read() терпит неудачу. Вероятно, было прервано чтение из ptym.
*/
static void
sig_term(int signo)
{
	sigcaught = 1; /* просто установить флаг и вернуться */
}

void
do_driver(char *driver)
{
	pid_t child;
	int pipe[2];
	/*
	* Создать канал для взаимодействия с драйвером.
	*/
	if (fd_pipe(pipe) < 0)
		err_sys("невозможно создать канал");
	if ((child = fork()) < 0) {
		err_sys("ошибка вызова функции fork");
	} else if (child == 0) { /* дочерний процесс */
		close(pipe[1]);
		/* stdin драйвера */
		if (dup2(pipe[0], STDIN_FILENO) != STDIN_FILENO)
			err_sys("ошибка вызова функции dup2 для stdin");
		/* stdout драйвера */
		if (dup2(pipe[0], STDOUT_FILENO) != STDOUT_FILENO)
			err_sys("ошибка вызова функции dup2 для stdout");
		if (pipe[0] != STDIN_FILENO && pipe[0] != STDOUT_FILENO)
			close(pipe[0]);
		/*оставить stderr драйвера неизменным */
		execlp(driver, driver, (char *)0);
		err_sys("ошибка вызова функции execlp для: %s", driver);
	}
	close(pipe[0]); /* родительский процесс */
	if (dup2(pipe[1], STDIN_FILENO) != STDIN_FILENO)
		err_sys("ошибка вызова функции dup2 для stdin");
	if (dup2(pipe[1], STDOUT_FILENO) != STDOUT_FILENO)
		err_sys("ошибка вызова функции dup2 для stdout");
	if (pipe[1] != STDIN_FILENO && pipe[1] != STDOUT_FILENO)
		close(pipe[1]);
	/*
	* Родительский процесс возвращает управление, но stdin и stdout
	* остаются связанными с драйвером.
	*/
}