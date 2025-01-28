#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_unix_socket"

int main() {
    int client_fd;
    struct sockaddr_un addr;
    char buffer[1024];

    // Создаем сокет
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Указываем путь к сокету
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Подключаемся к серверу
    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Подключение к серверу установлено!\n");

    // Отправляем данные серверу
    const char *message = "Привет от клиента!";
    write(client_fd, message, strlen(message));

    // Читаем ответ от сервера
    ssize_t num_bytes = read(client_fd, buffer, sizeof(buffer));
    if (num_bytes == -1) {
        perror("read");
    } else {
        buffer[num_bytes] = '\0';
        printf("Получено от сервера: %s\n", buffer);
    }

    // Закрываем сокет
    close(client_fd);

    return 0;
}