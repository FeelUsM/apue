#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define BUFFER_SIZE 1024

void handle_connection(int sock) {
    char buffer[BUFFER_SIZE];
    struct pollfd fds[2];
    int bytes_read;

    fds[0].fd = STDIN_FILENO; // Ввод с клавиатуры
    fds[0].events = POLLIN;
    fds[1].fd = sock; // Сокет сервера
    fds[1].events = POLLIN;

    while (1) {
        if (poll(fds, 2, -1) == -1) {
            perror("poll");
            break;
        }

        // Если есть данные от пользователя
        if (fds[0].revents & POLLIN) {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) break;
            send(sock, buffer, bytes_read, 0);
        }

        // Если есть данные от сервера
        if (fds[1].revents & POLLIN) {
            bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
            if (bytes_read <= 0) break;
            write(STDOUT_FILENO, buffer, bytes_read);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <IP-адрес> <Порт>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int sock;
    struct sockaddr_in server_addr;

    // Создаем сокет
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        return EXIT_FAILURE;
    }

    // Подключаемся к серверу
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Подключено к %s:%s\n", argv[1], argv[2]);
    handle_connection(sock);

    close(sock);
    return EXIT_SUCCESS;
}
