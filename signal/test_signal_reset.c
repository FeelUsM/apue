#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void handler(int){
	printf("hello from my handler\n");
}

int main(){
	char buf[100];
	buf[99]=0;
	signal(SIGINT,handler);
	for(int i=0; i<10; i++){
		errno = 0;
		unsigned x = sleep(5);
		printf("%u %d\n",x,errno); // sleep прерывается и не перезапускается (и возвращает, сколько он недоспал)
		perror("error");
		//fgets(buf,99,stdin); // read перезапускается
		//printf("<%s>\n",buf);
	}
}