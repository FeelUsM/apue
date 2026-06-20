#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>

static jmp_buf env_alrm;
static void
sig_alrm(int signo)
{
	printf("таймер истёк\n");
	longjmp(env_alrm, 1);
}

unsigned int
sleep2(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
	if (setjmp(env_alrm) == 0) {
		alarm(seconds); /* запустить таймер */
		printf("таймер запущен, ожидаю\n");
		pause(); /* следующий же перехваченный сигнал */
		/* возобновить работу процесса */
	}
	return(alarm(0)); /* выключить таймер и вернуть время, */
	/* оставшееся до его истечения */
}

static void
sig_int(int signo)
{
	int i, j;
	volatile int k;
	/*
	* Настройте параметры циклов так, чтобы они выполнялись
	* дольше 5 секунд в системе, где запускается программа.
	*/
	printf("\nфункция sig_int начала обработку\n");
		for (i = 0; i < 300000; i++)
			for (j = 1; j < 4000; j++)
				k += i / j;
	printf("функция sig_int закончила обработку\n");
}

int
main(void)
{
	unsigned int unslept;
	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("ошибка вызова функции signal(SIGINT)");
	unslept = sleep2(5); 
	/*
	sleep2 прерывает sig_int и не возвращаетсся к его обработке из-за longjmp
	со стандартным sleep так не происходит
	*/
	printf("функция sleep2 вернула значение: %u\n", unslept);
	exit(0);
}
