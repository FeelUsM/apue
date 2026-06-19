/*
отключаем echo-режим в терминале
*/

#include <signal.h>
#include <stdio.h>
#include <termios.h>

#define MAX_PASS_LEN 8 /* максимальное количество символов в пароле */
char *
getpass(const char *prompt)
{
	static char buf[MAX_PASS_LEN + 1]; /* нулевой байт в конце */
	char *ptr;
	sigset_t sig, osig;
	struct termios ts, ots;
	FILE *fp;
	int c;

	if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
		return(NULL);
	setbuf(fp, NULL);
	sigemptyset(&sig);
	sigaddset(&sig, SIGINT); /* заблокировать SIGINT */
	sigaddset(&sig, SIGTSTP); /* заблокировать SIGTSTP */
	sigprocmask(SIG_BLOCK, &sig, &osig); /* сохранить маску */
	
	tcgetattr(fileno(fp), &ts); /* сохранить состояние терминала */
	ots = ts; /* скопировать структуру */
	ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(fileno(fp), TCSAFLUSH, &ts);
	fputs(prompt, fp);

	ptr = buf;
	while ((c = getc(fp)) != EOF && c != '\n')
		if (ptr < &buf[MAX_PASS_LEN])
			*ptr++ = c;
	*ptr = 0; /* завершающий нулевой символ */
//    if (fgets(buf, sizeof(buf), stdin) == NULL) {
//        return NULL;
//    } 
//  надо ещё перевод строки вконце убрать
	putc('\n', fp); /* вывести символ перевода строки */
	tcsetattr(fileno(fp), TCSAFLUSH, &ots); /* восстановить состояние терминала */
	sigprocmask(SIG_SETMASK, &osig, NULL); /* восстановить маску */
	fclose(fp); /* завершить работу с /dev/tty */
	return(buf);
}

int
main(void)
{
	char *ptr;
	if ((ptr = getpass("Введите пароль:")) == NULL)
		perror("ошибка вызова функции getpass");
	printf("пароль: %s\n", ptr);
	for(const char * p = ptr; *p; p++){
		if(*p>=0x20) printf("%c",*p);
		else printf("\\x%02hhX",*p);
	}
	printf("\n");
	/* здесь можно работать с паролем (например, зашифровать его) ... */
	while (*ptr != 0)
		*ptr++ = 0; /* забить нулями, когда он стал больше не нужен */
	//exit(0);
}