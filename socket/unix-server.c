#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_unix_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[1024];

    // Создаем сокет
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Указываем путь к сокету
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Удаляем старый сокет, если он существует
    unlink(SOCKET_PATH);

    // Привязываем сокет к адресу
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Ожидаем подключения клиентов
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Сервер ожидает подключения...\n");

    // Принимаем подключение
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Клиент подключен!\n");

    // Читаем данные от клиента
    ssize_t num_bytes = read(client_fd, buffer, sizeof(buffer)-1 );
    if (num_bytes == -1) {
        perror("read");
    } else {
        buffer[num_bytes] = '\0';
        printf("Получено от клиента: %s\n", buffer);
    }

    // Отправляем ответ клиенту
    const char *response = "Привет от сервера!";
    write(client_fd, response, strlen(response));

    // Закрываем сокеты
    close(client_fd);
    close(server_fd);

    // Удаляем файл сокета
    unlink(SOCKET_PATH);

    return 0;
}