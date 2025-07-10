#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void * foo(void *){
	while(1);
}

int main(){
	pthread_t tid;
	if(pthread_create(&tid,NULL,foo,NULL)!=0)
		return 33;
	sleep(1);
	exit(0);
}
