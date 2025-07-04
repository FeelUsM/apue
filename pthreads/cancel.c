#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread2(void *){
	printf("thread2 start reading\n");
	getchar();
	printf("thread2 ends\n");
}

int main(){
	// запускаем thread2
	printf("PTHREAD_CANCEL_DEFERRED = %d\nPTHREAD_CANCEL_ASYNCHRONOUS = %d\nPTHREAD_CANCEL_ENABLE = %d\nPTHREAD_CANCEL_DISABLE = %d\n",
		PTHREAD_CANCEL_DEFERRED,PTHREAD_CANCEL_ASYNCHRONOUS,PTHREAD_CANCEL_ENABLE,PTHREAD_CANCEL_DISABLE);


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