#define USE_ERR
#include "apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int
main(int argc, char *argv[])
{
	int val;
	if (argc != 2)
		err_quit("Использование: a.out <номер_дескриптора>");
	int fd = atoi(argv[1]);
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("ошибка fcntl для дескриптора %d", fd);
	switch (val & O_ACCMODE) {
		case O_RDONLY:
			printf("только для чтения");
			break;
		case O_WRONLY:
			printf("только для записи");
			break;
		case O_RDWR: {
			printf("для чтения и для записи");
			//#define BUFSIZ 1000
			char buf[BUFSIZ];
			const char * s = "hello ";
			int l;

			// r1 from 0
			if((l=read(fd,buf,BUFSIZ-1))==-1)
				err_sys("ошибка чтения");
			buf[l]=0;
			printf("r1 from 0 : '%s' (%ld)\n",buf,lseek(fd,0,SEEK_CUR));
			// w2 to end
			if(write(fd,s,strlen(s))==-1)
				err_sys("ошибка записи");
			printf("w2 to end +(%ld) : (%ld)\n",strlen(s),lseek(fd,0,SEEK_CUR));
			// r3 from end
			if((l=read(fd,buf,BUFSIZ-1))==-1)
				err_sys("ошибка чтения");
			buf[l]=0;
			printf("r3 from end : '%s' (%ld)\n",buf,lseek(fd,0,SEEK_CUR));

			if(lseek(fd,0,SEEK_SET)!=0)
				err_sys("ошибка позиционирования");
			// r4 from 0
			if((l=read(fd,buf,BUFSIZ-1))==-1)
				err_sys("ошибка чтения");
			buf[l]=0;
			printf("r4 from 0 : '%s' (%ld)\n",buf,lseek(fd,0,SEEK_CUR));

			if(lseek(fd,0,SEEK_SET)!=0)
				err_sys("ошибка позиционирования");
			// w5 to 0
			if(write(fd,s,strlen(s))==-1)
				err_sys("ошибка записи");
			printf("w5 to 0 +(%ld) : (%ld)\n",strlen(s),lseek(fd,0,SEEK_CUR));

			if(lseek(fd,0,SEEK_SET)!=0)
				err_sys("ошибка позиционирования");
			// r6 from 0
			if((l=read(fd,buf,BUFSIZ-1))==-1)
				err_sys("ошибка чтения");
			buf[l]=0;
			printf("r6 from 0 : '%s' (%ld)\n",buf,lseek(fd,0,SEEK_CUR));

			break;
		}
		default:
			err_dump("неизвестный режим доступа");
	}
	if (val & O_APPEND)
		printf(", добавление в конец");
	if (val & O_NONBLOCK)
		printf(", неблокирующий режим");
	if (val & O_SYNC)
		printf(", синхронный режим записи");
	#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(", синхронный режим записи");
	#endif
	putchar('\n');
	exit(0);
}