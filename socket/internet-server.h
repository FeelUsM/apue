#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Привет от сервера!";

    // Создаем сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Сокет не создан");
        exit(EXIT_FAILURE);
    }

    // Настраиваем адрес сервера
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Принимаем подключения на все интерфейсы
    address.sin_port = htons(PORT);

    // Привязываем сокет к адресу
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Слушаем входящие подключения
    if (listen(server_fd, 3) < 0) {
        perror("Ошибка прослушивания");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Сервер слушает на порту %d...\n", PORT);

    // Принимаем подключение
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Ошибка принятия подключения");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Читаем данные от клиента
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Сообщение от клиента: %s\n", buffer);

    // Отправляем ответ клиенту
    send(new_socket, hello, strlen(hello), 0);
    printf("Ответ отправлен клиенту.\n");

    // Закрываем сокеты
    close(new_socket);
    close(server_fd);
    return 0;
}