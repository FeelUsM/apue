#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void hook(int){
	printf("Ctrl-C hooked, to interrupt use Ctrl+\\\n");
}

int main(){
	if(signal(SIGINT,hook)==SIG_ERR){
		fprintf(stderr,"failed to setup signal hook\n");
		exit(1);
	}
	printf("start\n");
	char buf[100];
	fgets(buf,100,stdin);
	printf("stop\n");
}