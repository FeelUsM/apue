#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHARED_MEM_SIZE 1024  // Размер shared memory

int main() {
    const char *shared_mem_name = "/my_shared_memory";
    int shm_fd;
    void *ptr;

    // Создаем shared memory объект
    shm_fd = shm_open(shared_mem_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Маппируем shared memory в адресное пространство процесса
    ptr = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // В другом процессе можно прочитать эти данные
    printf("Данные в shared memory: %s\n", (char *)ptr);

    // Убираем маппинг
    if (munmap(ptr, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Закрываем shared memory объект
    if (close(shm_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}