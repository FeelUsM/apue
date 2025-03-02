#include <stdio.h>
#include <unistd.h>
int main(){
	printf("введите\n");
	pid_t f = fork();
	pid_t pid = getpid();
	printf("%d: число\n",pid);
	if(f==0)
		sleep(2);
	int x;
	scanf("%d",&x);
	printf("%d: вы ввели %d\n",pid,x);
}
