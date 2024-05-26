#define USE_ERR
#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("Использование: a.out <dirname>");

#ifdef ARG_MAX
	printf("ARG_MAX defined as %ld\t", (long)ARG_MAX+0);
#else
	printf("ARG_MAX not defined\t");
#endif
#ifdef _SC_ARG_MAX
	pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
#else
	printf("_SC_ARG_MAX not found\n");
#endif

#ifdef ATEXIT_MAX
	printf("ATEXIT_MAX defined as %ld\t", (long)ATEXIT_MAX+0);
#else
	printf("ATEXIT_MAX not defined\t");
#endif
#ifdef _SC_ATEXIT_MAX
	pr_sysconf("ATEXIT_MAX =", _SC_ATEXIT_MAX);
#else
	printf("_SC_ATEXIT_MAX not found\n");
#endif

#ifdef CHILD_MAX
	printf("CHILD_MAX defined as %ld\t", (long)CHILD_MAX+0);
#else
	printf("CHILD_MAX not defined\t");
#endif
#ifdef _SC_CHILD_MAX
	pr_sysconf("CHILD_MAX =", _SC_CHILD_MAX);
#else
	printf("_SC_CHILD_MAX not found\n");
#endif

#ifdef CLK_TCK
	printf("CLK_TCK defined as %ld\t", (long)CLK_TCK+0);
#else
	printf("CLK_TCK not defined\t");
#endif
#ifdef _SC_CLK_TCK
	pr_sysconf("CLK_TCK =", _SC_CLK_TCK);
#else
	printf("_SC_CLK_TCK not found\n");
#endif

#ifdef COLL_WEIGHTS_MAX
	printf("COLL_WEIGHTS_MAX defined as %ld\t", (long)COLL_WEIGHTS_MAX+0);
#else
	printf("COLL_WEIGHTS_MAX not defined\t");
#endif
#ifdef _SC_COLL_WEIGHTS_MAX
	pr_sysconf("COLL_WEIGHTS_MAX =", _SC_COLL_WEIGHTS_MAX);
#else
	printf("_SC_COLL_WEIGHTS_MAX not found\n");
#endif

#ifdef DELAYTIMER_MAX
	printf("DELAYTIMER_MAX defined as %ld\t", (long)DELAYTIMER_MAX+0);
#else
	printf("DELAYTIMER_MAX not defined\t");
#endif
#ifdef _SC_DELAYTIMER_MAX
	pr_sysconf("DELAYTIMER_MAX =", _SC_DELAYTIMER_MAX);
#else
	printf("_SC_DELAYTIMER_MAX not found\n");
#endif

#ifdef HOST_NAME_MAX
	printf("HOST_NAME_MAX defined as %ld\t", (long)HOST_NAME_MAX+0);
#else
	printf("HOST_NAME_MAX not defined\t");
#endif
#ifdef _SC_HOST_NAME_MAX
	pr_sysconf("HOST_NAME_MAX =", _SC_HOST_NAME_MAX);
#else
	printf("_SC_HOST_NAME_MAX not found\n");
#endif

#ifdef IOV_MAX
	printf("IOV_MAX defined as %ld\t", (long)IOV_MAX+0);
#else
	printf("IOV_MAX not defined\t");
#endif
#ifdef _SC_IOV_MAX
	pr_sysconf("IOV_MAX =", _SC_IOV_MAX);
#else
	printf("_SC_IOV_MAX not found\n");
#endif

#ifdef LINE_MAX
	printf("LINE_MAX defined as %ld\t", (long)LINE_MAX+0);
#else
	printf("LINE_MAX not defined\t");
#endif
#ifdef _SC_LINE_MAX
	pr_sysconf("LINE_MAX =", _SC_LINE_MAX);
#else
	printf("_SC_LINE_MAX not found\n");
#endif

#ifdef LOGIN_NAME_MAX
	printf("LOGIN_NAME_MAX defined as %ld\t", (long)LOGIN_NAME_MAX+0);
#else
	printf("LOGIN_NAME_MAX not defined\t");
#endif
#ifdef _SC_LOGIN_NAME_MAX
	pr_sysconf("LOGIN_NAME_MAX =", _SC_LOGIN_NAME_MAX);
#else
	printf("_SC_LOGIN_NAME_MAX not found\n");
#endif

#ifdef OPEN_MAX
	printf("OPEN_MAX defined as %ld\t", (long)OPEN_MAX+0);
#else
	printf("OPEN_MAX not defined\t");
#endif
#ifdef _SC_OPEN_MAX
	pr_sysconf("OPEN_MAX =", _SC_OPEN_MAX);
#else
	printf("_SC_OPEN_MAX not found\n");
#endif

#ifdef PAGESIZE
	printf("PAGESIZE defined as %ld\t", (long)PAGESIZE+0);
#else
	printf("PAGESIZE not defined\t");
#endif
#ifdef _SC_PAGESIZE
	pr_sysconf("PAGESIZE =", _SC_PAGESIZE);
#else
	printf("_SC_PAGESIZE not found\n");
#endif

#ifdef PAGE_SIZE
	printf("PAGE_SIZE defined as %ld\t", (long)PAGE_SIZE+0);
#else
	printf("PAGE_SIZE not defined\t");
#endif
#ifdef _SC_PAGE_SIZE
	pr_sysconf("PAGE_SIZE =", _SC_PAGE_SIZE);
#else
	printf("_SC_PAGE_SIZE not found\n");
#endif

#ifdef RE_DUP_MAX
	printf("RE_DUP_MAX defined as %ld\t", (long)RE_DUP_MAX+0);
#else
	printf("RE_DUP_MAX not defined\t");
#endif
#ifdef _SC_RE_DUP_MAX
	pr_sysconf("RE_DUP_MAX =", _SC_RE_DUP_MAX);
#else
	printf("_SC_RE_DUP_MAX not found\n");
#endif

#ifdef RTSIG_MAX
	printf("RTSIG_MAX defined as %ld\t", (long)RTSIG_MAX+0);
#else
	printf("RTSIG_MAX not defined\t");
#endif
#ifdef _SC_RTSIG_MAX
	pr_sysconf("RTSIG_MAX =", _SC_RTSIG_MAX);
#else
	printf("_SC_RTSIG_MAX not found\n");
#endif

#ifdef SEM_NSEMS_MAX
	printf("SEM_NSEMS_MAX defined as %ld\t", (long)SEM_NSEMS_MAX+0);
#else
	printf("SEM_NSEMS_MAX not defined\t");
#endif
#ifdef _SC_SEM_NSEMS_MAX
	pr_sysconf("SEM_NSEMS_MAX =", _SC_SEM_NSEMS_MAX);
#else
	printf("_SC_SEM_NSEMS_MAX not found\n");
#endif

#ifdef SEM_VALUE_MAX
	printf("SEM_VALUE_MAX defined as %ld\t", (long)SEM_VALUE_MAX+0);
#else
	printf("SEM_VALUE_MAX not defined\t");
#endif
#ifdef _SC_SEM_VALUE_MAX
	pr_sysconf("SEM_VALUE_MAX =", _SC_SEM_VALUE_MAX);
#else
	printf("_SC_SEM_VALUE_MAX not found\n");
#endif

#ifdef SIGQUEUE_MAX
	printf("SIGQUEUE_MAX defined as %ld\t", (long)SIGQUEUE_MAX+0);
#else
	printf("SIGQUEUE_MAX not defined\t");
#endif
#ifdef _SC_SIGQUEUE_MAX
	pr_sysconf("SIGQUEUE_MAX =", _SC_SIGQUEUE_MAX);
#else
	printf("_SC_SIGQUEUE_MAX not found\n");
#endif

#ifdef STREAM_MAX
	printf("STREAM_MAX defined as %ld\t", (long)STREAM_MAX+0);
#else
	printf("STREAM_MAX not defined\t");
#endif
#ifdef _SC_STREAM_MAX
	pr_sysconf("STREAM_MAX =", _SC_STREAM_MAX);
#else
	printf("_SC_STREAM_MAX not found\n");
#endif

#ifdef SYMLOOP_MAX
	printf("SYMLOOP_MAX defined as %ld\t", (long)SYMLOOP_MAX+0);
#else
	printf("SYMLOOP_MAX not defined\t");
#endif
#ifdef _SC_SYMLOOP_MAX
	pr_sysconf("SYMLOOP_MAX =", _SC_SYMLOOP_MAX);
#else
	printf("_SC_SYMLOOP_MAX not found\n");
#endif

#ifdef TIMER_MAX
	printf("TIMER_MAX defined as %ld\t", (long)TIMER_MAX+0);
#else
	printf("TIMER_MAX not defined\t");
#endif
#ifdef _SC_TIMER_MAX
	pr_sysconf("TIMER_MAX =", _SC_TIMER_MAX);
#else
	printf("_SC_TIMER_MAX not found\n");
#endif

#ifdef TTY_NAME_MAX
	printf("TTY_NAME_MAX defined as %ld\t", (long)TTY_NAME_MAX+0);
#else
	printf("TTY_NAME_MAX not defined\t");
#endif
#ifdef _SC_TTY_NAME_MAX
	pr_sysconf("TTY_NAME_MAX =", _SC_TTY_NAME_MAX);
#else
	printf("_SC_TTY_NAME_MAX not found\n");
#endif

#ifdef TZNAME_MAX
	printf("TZNAME_MAX defined as %ld\t", (long)TZNAME_MAX+0);
#else
	printf("TZNAME_MAX not defined\t");
#endif
#ifdef _SC_TZNAME_MAX
	pr_sysconf("TZNAME_MAX =", _SC_TZNAME_MAX);
#else
	printf("_SC_TZNAME_MAX not found\n");
#endif

printf("\n");

#ifdef FILESIZEBITS
	printf("FILESIZEBITS defined as %ld\t", (long)FILESIZEBITS+0);
#else
	printf("FILESIZEBITS not defined\t");
#endif
#ifdef _PC_FILESIZEBITS
	pr_pathconf("FILESIZEBITS =", argv[1], _PC_FILESIZEBITS);
#else
	printf("_PC_FILESIZEBITS not found\n");
#endif

#ifdef LINK_MAX
	printf("LINK_MAX defined as %ld\t", (long)LINK_MAX+0);
#else
	printf("LINK_MAX not defined\t");
#endif
#ifdef _PC_LINK_MAX
	pr_pathconf("LINK_MAX =", argv[1], _PC_LINK_MAX);
#else
	printf("_PC_LINK_MAX not found\n");
#endif

#ifdef MAX_CANON
	printf("MAX_CANON defined as %ld\t", (long)MAX_CANON+0);
#else
	printf("MAX_CANON not defined\t");
#endif
#ifdef _PC_MAX_CANON
	pr_pathconf("MAX_CANON =", argv[1], _PC_MAX_CANON);
#else
	printf("_PC_MAX_CANON not found\n");
#endif

#ifdef MAX_INPUT
	printf("MAX_INPUT defined as %ld\t", (long)MAX_INPUT+0);
#else
	printf("MAX_INPUT not defined\t");
#endif
#ifdef _PC_MAX_INPUT
	pr_pathconf("MAX_INPUT =", argv[1], _PC_MAX_INPUT);
#else
	printf("_PC_MAX_INPUT not found\n");
#endif

#ifdef NAME_MAX
	printf("NAME_MAX defined as %ld\t", (long)NAME_MAX+0);
#else
	printf("NAME_MAX not defined\t");
#endif
#ifdef _PC_NAME_MAX
	pr_pathconf("NAME_MAX =", argv[1], _PC_NAME_MAX);
#else
	printf("_PC_NAME_MAX not found\n");
#endif

#ifdef PATH_MAX
	printf("PATH_MAX defined as %ld\t", (long)PATH_MAX+0);
#else
	printf("PATH_MAX not defined\t");
#endif
#ifdef _PC_PATH_MAX
	pr_pathconf("PATH_MAX =", argv[1], _PC_PATH_MAX);
#else
	printf("_PC_PATH_MAX not found\n");
#endif

#ifdef PIPE_BUF
	printf("PIPE_BUF defined as %ld\t", (long)PIPE_BUF+0);
#else
	printf("PIPE_BUF not defined\t");
#endif
#ifdef _PC_PIPE_BUF
	pr_pathconf("PIPE_BUF =", argv[1], _PC_PIPE_BUF);
#else
	printf("_PC_PIPE_BUF not found\n");
#endif

#ifdef _POSIX_TIMESTAMP_RESOLUTION
	printf("_POSIX_TIMESTAMP_RESOLUTION defined as %ld\t", (long)_POSIX_TIMESTAMP_RESOLUTION+0);
#else
	printf("_POSIX_TIMESTAMP_RESOLUTION not defined\t");
#endif
#ifdef _PC_TIMESTAMP_RESOLUTION
	pr_pathconf("_POSIX_TIMESTAMP_RESOLUTION =", argv[1], _PC_TIMESTAMP_RESOLUTION);
#else
	printf("_PC_TIMESTAMP_RESOLUTION not found\n");
#endif

#ifdef SYMLINK_MAX
	printf("SYMLINK_MAX defined as %ld\t", (long)SYMLINK_MAX+0);
#else
	printf("SYMLINK_MAX not defined\t");
#endif
#ifdef _PC_SYMLINK_MAX
	pr_pathconf("SYMLINK_MAX =", argv[1], _PC_SYMLINK_MAX);
#else
	printf("_PC_SYMLINK_MAX not found\n");
#endif

	exit(0);
}

static void
pr_sysconf(char *mesg, int name)
{
	long val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = sysconf(name)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs(" (не поддерживается)\n", stdout);
			else
				err_sys("ошибка вызова sysconf");
		} else {
			fputs(" (нет ограничений)\n", stdout);
		}
	} else {
		printf(" %ld\n", val);
	}
}

static void
pr_pathconf(char *mesg, char *path, int name)
{
	long val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = pathconf(path, name)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs(" (не поддерживается)\n", stdout);
			else
				err_sys("ошибка вызова pathconf, path = %s", path);
		} else {
			fputs(" (нет ограничений)\n", stdout);
		}
	} else {
		printf(" %ld\n", val);
	}
}
