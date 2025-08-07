#include <stdio.h>
//#include <grp.h>
#include <unistd.h>

int main(){
	gid_t grps[100];
	int len = getgroups(100,grps);
	for(int i=0; i<len; i++)
		printf("%d\n",grps[i]);
}