#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a = 3;
int b;

int main(int argc, const char ** argv){
	int c;
	printf("%p - code\n",main);
	printf("%p - global initialized\n",&a);
	printf("%p - global uninitialized\n",&b);
	printf("%p - heap\n",malloc(4));
	printf("%p - stack\n",&c);
	printf("%p - argv[0]\n",argv[0]);
	printf("%p - environ[0]\n",environ[0]);
	printf("%p - environ\n",environ);
	printf("%p - argv\n",argv);
}
