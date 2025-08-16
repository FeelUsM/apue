#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void hook(int){
    printf("i am hook of %zx\n",(size_t)pthread_self());
}

void * thread2(void *) {
	// set signal hook
	struct sigaction sa, osa;
	sa.sa_handler = hook;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGUSR1,&sa,&osa)==-1){
		fprintf(stderr,"failed to setup signal hook\n");
		exit(1);
	}

	// blocking reading
	printf("thread2 start reading\n");
	char buf[100];
	fgets(buf,100,stdin);
	printf("thread2 ends\n");
}

int main(){
	pthread_t t;
	if(0!=pthread_create(&t,NULL,thread2,NULL)){
		printf("cannot create thread\n");
		exit(1);
	}

	sleep(2);

	pthread_kill(t,SIGUSR1);
	pthread_join(t,NULL);

	printf("main exit\n");
}