/*
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int fn(const char * path, const struct stat *ptr, int flag) {
	printf("%s\n",path);
}

int main(){
	if (ftw(".", fn, 10) != 0) {
    	perror("ftw"); exit(2);
	}
}
*/
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int
display_info(const char *fpath, const struct stat *sb,
            int tflag/*, struct FTW *ftwbuf*/)
{
   printf(//"%-3s %2d ",
          "%-3s ",
           (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
           (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "f" :
           (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
           (tflag == FTW_SLN) ? "sln" : "???"
           /*, ftwbuf->level*/);

   if (tflag == FTW_NS)
       printf("-------");
   else
       printf("%7jd", (intmax_t) sb->st_size);

   printf(//"   %-40s %d %s\n",
          "   %-40s\n",
           fpath/*, ftwbuf->base, fpath + ftwbuf->base*/);

   return 0;           /* To tell nftw() to continue */
}

int
main(int argc, char *argv[])
{
   int flags = 0;

   if (argc > 2 && strchr(argv[2], 'd') != NULL)
       flags |= FTW_DEPTH;
   if (argc > 2 && strchr(argv[2], 'p') != NULL)
       flags |= FTW_PHYS;

   if (/*n*/ftw((argc < 2) ? "." : argv[1], display_info, 20/*, flags*/)
           == -1) {
       perror("nftw");
       exit(EXIT_FAILURE);
   }

   exit(EXIT_SUCCESS);
}