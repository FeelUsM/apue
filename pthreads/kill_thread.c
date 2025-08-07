#include <setjmp.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

static jmp_buf jump_buffer;
// static volatile sig_atomic_t 
static volatile int jump_ready = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void handler(int sig) {
	pthread_mutex_lock(&mut); // lock 2
    if (jump_ready) {
        printf("Signal received. Jumping...\n");
        longjmp(jump_buffer, 1);
    } else {
        printf("Jump buffer not ready!\n");
    }
	pthread_mutex_unlock(&mut); // unlock 2
}

void * thread2(void *){
	printf("thread2 start reading\n");

    sigset_t oset;
    if(pthread_sigmask(SIG_SETMASK, NULL, &oset)!=0){
        printf("thread2: error pthread_sigmask()\n");
    }
    else{
        printf("thread2: next signals are disabled\n");
        if (sigismember(&oset, SIGUSR1))        printf(" SIGUSR1(%d) ",SIGUSR1);
        if (sigismember(&oset, SIGINT))        printf(" SIGINT(%d) ",SIGINT);
        if (sigismember(&oset, SIGQUIT))        printf(" SIGQUIT(%d) ",SIGQUIT);
        if (sigismember(&oset, SIGUSR1))        printf(" SIGUSR1(%d) ",SIGUSR1);
        if (sigismember(&oset, SIGALRM))        printf(" SIGALRM(%d) ",SIGALRM);
    }

	pthread_mutex_lock(&mut); // lock 1
    if (setjmp(jump_buffer) == 0) {
        jump_ready = 1;  // Помечаем, что теперь можно прыгать
		pthread_mutex_unlock(&mut); // unlock 1
        printf("Waiting for SIGINT..., %d\n",jump_ready);
        //getchar(); // glibc начинает глючить и не хочет завершать программу по exit(0); только ОС может завершить всё по _exit()
        char buf[100];
        read(0,buf,1);
        printf("blocking over\n");
    } else {
		pthread_mutex_unlock(&mut); // unlock 2
        printf("Jumped back from signal\n");
    }
    jump_ready = 0;  // Помечаем, что теперь можно прыгать
    pthread_exit(0);
}

int main(){
    signal(SIGUSR1, handler);
	// устанавливаем обработчик
	// запускаем thread2
	pthread_t thr2;
	pthread_create(&thr2, NULL, thread2, NULL);
	// спим секунду
	sleep(2);
	// пытаемся его убить
	printf("killing thr2\n");
	pthread_kill(thr2,SIGUSR1);
	pthread_join(thr2, NULL);
	printf("main exit\n");

	// int saved_fd0 = dup(0);     // скопируем stdin
	//fclose(stdin);              // закроем FILE* и fd 0
	// dup2(saved_fd0, 0);         // восстановим fd 0
	// close(saved_fd0);           // закрываем временный дубликат
	// stdin = fdopen(0, "r");     // создаём новый FILE* поверх fd 0
	// ^ не помогло исправить getchar()
	exit(0);
}