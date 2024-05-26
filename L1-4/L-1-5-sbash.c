#define USE_ERR
#include "apue.h"
#include <sys/wait.h>
int
main(void)
{
	char buf[MAXLINE]; /* из apue.h */
	pid_t pid;
	int status;
	printf("%% "); /* вывести приглашение (printf требует использовать */
	/* последовательность %%, чтобы вывести символ %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = 0; /* заменить символ перевода строки */
		if ((pid = fork()) < 0) {
			err_sys("ошибка вызова fork");
		} else if (pid == 0) { /* дочерний процесс */
			execlp(buf, buf, (char *)0);
			err_ret("невозможно выполнить: %s", buf);
			exit(127);
		}
		/* родительский процесс */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("ошибка вызова waitpid");
		printf("%% ");
	}
	exit(0);
}