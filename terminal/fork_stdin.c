/*
? какой процесс будет получать ввод: родительский или дочерний
- по очереди
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void echo(const char * prompt){
	for(;;){
		char buf[1000];
		size_t len;
		if((len = read(0,buf,999))>0){
			buf[len]=0;
			printf("%s: %s",prompt,buf);
		}
		else{
			exit(0);
		}
	}
}

int main(){
	if(fork()==0){
		sleep(2);
		echo("child");
	}
	else{
		echo("parent");
	}
}
