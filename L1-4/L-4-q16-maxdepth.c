#define USE_ERR
#include "apue.h"
#include <sys/stat.h>
#include <unistd.h>

int main(){
	size_t pathlen=0;
	char * path = path_alloc(&pathlen);
	#define limit 5000
	for(int i=1; i<limit; i++){
		if(mkdir("test",DIR_MODE)==-1)
			err_sys("can not create dir");
		if(chdir("test")==-1) 
			err_sys("can not change cur dir");
		if(i%100==0){
			printf("%d ",i);
			char * tmp;
			while((tmp = getcwd(path,pathlen-1))==NULL && pathlen<i*5+100){
				err_ret("for depth %d not enoth %lu buffer. do realloc",i,pathlen);
				pathlen *=2;
				char * tmp2 = path;
				free(path);
				if ((path = malloc(pathlen)) == NULL)
					err_sys("ошибка вызова realloc with size %lu",pathlen);
			}
			if(tmp==NULL){
				err_sys("for depth %d not enoth %lu buffer. exit",i,pathlen);
			}
		}
	}
	free(path);
	printf("%d nested dirs created successfully\n",limit);
}