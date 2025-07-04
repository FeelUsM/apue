#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread2(void *){
	int ctype;
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,&ctype);
	if(ctype==PTHREAD_CANCEL_DEFERRED)
		printf("thread2 start calculating (PTHREAD_CANCEL_DEFERRED)\n");
	else if(ctype==PTHREAD_CANCEL_ASYNCHRONOUS)
		printf("thread2 start calculating (PTHREAD_CANCEL_ASYNCHRONOUS)\n");
	else
		printf("thread2 start calculating (???)\n");
	pthread_setcanceltype(ctype,&ctype);
	int x=1;
	while(1){ x++; }
	printf("thread2 ends\n");
}

int main(){
	// запускаем thread2
	pthread_t thr2;
	pthread_create(&thr2, NULL, thread2, NULL);
	// спим секунду
	sleep(2);
	// пытаемся его убить
	printf("killing thr2\n");
	pthread_cancel(thr2);
	pthread_join(thr2, NULL);
	printf("main exit\n");
}