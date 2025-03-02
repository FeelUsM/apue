#include <stdio.h>
#include <unistd.h>

int main(){
	for(char ** ppc=environ; ppc!=NULL; ppc++){
		printf("%s\n",*ppc);
	}
}
