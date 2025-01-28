#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

void check_rss_limit() {
    struct rlimit rl;

    // Получаем текущие ограничения на резидентный набор памяти (RSS)
    if (getrlimit(RLIMIT_RSS, &rl) != 0) {
        perror("Ошибка getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Текущее ограничение на резидентный набор памяти (RSS): %ld байт = %g Gb\n", 
        (long)rl.rlim_cur, (double)rl.rlim_cur / (1024 * 1024 * 1024));

    printf("Максимальное ограничение на резидентный набор памяти (RSS): %ld байт = %g Gb\n", 
        (long)rl.rlim_max, (double)rl.rlim_max / (1024 * 1024 * 1024));

    if (getrlimit(RLIMIT_AS, &rl) != 0) {
        perror("Ошибка getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Текущее ограничение на виртувльную память (RSS): %ld байт = %g Gb\n", 
        (long)rl.rlim_cur, (double)rl.rlim_cur / (1024 * 1024 * 1024));

    printf("Максимальное ограничение на виртувльную память (RSS): %ld байт = %g Gb\n", 
        (long)rl.rlim_max, (double)rl.rlim_max / (1024 * 1024 * 1024));
}

int probe_memory(long int limit) {
    printf("start test until %ld = %gG\n",limit,limit/1024./1024./1024.);
    for(long int i=16; i<=limit; i*=2) {
        printf("try %ld (%gG):",i,i/1024./1024./1024.);
        fflush(stdout);
        char * p = malloc(i);
        for(long int j=0; j<i; j++) {
            p[j]=i%256;
        }
        printf("OK %d\n",p[i-1]);
        free(p);
    }
}

int main(int argc, const char * argv[]) {
    check_rss_limit();
    printf("int:%ld, long int:%ld, long long int:%ld\n",sizeof(int),sizeof(long int),sizeof(long long int));
    long int s = atol(argv[1]);
    probe_memory(s);
    return 0;
}