#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Привет от клиента!";

    // Создаем сокет
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Сокет не создан");
        return -1;
    }

    // Настраиваем адрес сервера
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразуем IP-адрес из текстового в бинарный формат
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Ошибка преобразования адреса");
        return -1;
    }

    // Подключаемся к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Ошибка подключения");
        return -1;
    }

    // Отправляем сообщение серверу
    send(sock, hello, strlen(hello), 0);
    printf("Сообщение отправлено серверу.\n");

    // Читаем ответ от сервера
    read(sock, buffer, BUFFER_SIZE);
    printf("Ответ от сервера: %s\n", buffer);

    // Закрываем сокет
    close(sock);
    return 0;
}