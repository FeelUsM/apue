#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void hook(int){
	printf("Ctrl-C hooked, to interrupt use Ctrl+\\\n");
}

int main(){
	struct sigaction sa, osa;
	sa.sa_handler = hook;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGINT,&sa,&osa)==-1){
		fprintf(stderr,"failed to setup signal hook\n");
		exit(1);
	}
	printf("start\n");
	char buf[100];
	fgets(buf,100,stdin);
	printf("stop\n");
}