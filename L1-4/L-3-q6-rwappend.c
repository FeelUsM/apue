#define USE_ERR
#include "apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, const char * argv[]) {
	if (argc != 2)
		err_quit("Использование: a.out filename");
	int fd = open(argv[1], O_RDWR|O_APPEND);
	if(fd==-1)
		err_sys("не могу открыть %s",argv[1]);

	// pos
	printf("start from %ld\n",lseek(fd,0,SEEK_CUR));

	char buf[10];
	int l;
	// r0 from 0 5 bytes
	if(lseek(fd,0,SEEK_SET)!=0)
		err_sys("ошибка позиционирования");
	if((l=read(fd,buf,5))==-1)
		err_sys("ошибка чтения");
	buf[l]=0;
	printf("r0 from 0 5 bytes : '%s' (%ld)\n",buf,lseek(fd,0,SEEK_CUR));

	char * s = "hello ";
	// w1 to end
	if(write(fd,s,strlen(s))==-1)
		err_sys("ошибка записи");
	printf("w1 to end +(%ld) : (%ld)\n",strlen(s),lseek(fd,0,SEEK_CUR));
}