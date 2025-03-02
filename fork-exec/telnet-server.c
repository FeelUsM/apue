#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pty.h>
#include <utmp.h>
#include <signal.h>
#include <errno.h>
#include <poll.h>

#define PORT 55555
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    int master_fd, slave_fd;
    char slave_name[256];
    pid_t pid;
    char buffer[BUFFER_SIZE+1];
    ssize_t bytes_read, bytes_written;
    struct pollfd fds[2];

    // Создаём новый псевдотерминал (PTY)
    if (openpty(&master_fd, &slave_fd, slave_name, NULL, NULL) == -1) {
        perror("openpty");
        exit(1);
    }

    // Форкаем процесс для запуска bash
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Дочерний процесс

        // Создаем новый сеанс
        setsid();

        // Связываем PTY с терминалом
        if (ioctl(slave_fd, TIOCSCTTY, 0) == -1) {
            perror("ioctl TIOCSCTTY");
            exit(1);
        }

        // Перенаправляем стандартные потоки
        dup2(slave_fd, STDIN_FILENO);
        dup2(slave_fd, STDOUT_FILENO);
        dup2(slave_fd, STDERR_FILENO);

        // Закрываем неиспользуемый master-дескриптор
        close(master_fd);
        close(slave_fd);

        // Отключаем буферизацию для корректного вывода
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);

        // Запускаем bash
        execl("/bin/bash", "/bin/bash", NULL);
        perror("execl");
        exit(1);
    }

    // Родительский процесс
    close(slave_fd); // В родителе закрываем slave_fd, он не нужен

    FILE *LOG = fopen("log.txt", "w");
    if (!LOG) {
        perror("fopen");
        close(client_socket);
        close(master_fd);
        return;
    }

    fprintf(LOG, "начинаю ретрансляцию\n");
    fflush(LOG);

    // Передаём данные между сокетом и PTY
    while (1) {
        fds[0].fd = client_socket;
        fds[0].events = POLLIN;
        fds[1].fd = master_fd;
        fds[1].events = POLLIN;

        if (poll(fds, 2, -1) == -1) {
            perror("poll");
            break;
        }

        // Чтение из сокета и запись в PTY
        if (fds[0].revents & POLLIN) {
            bytes_read = read(client_socket, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) break;
            buffer[bytes_read] = 0;
            fprintf(LOG, "input:%s\n", buffer);
            fflush(LOG);
            bytes_written = write(master_fd, buffer, bytes_read);
            if (bytes_written <= 0) break;
        }

        // Чтение из PTY и запись в сокет
        if (fds[1].revents & POLLIN) {
            bytes_read = read(master_fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) break;
            buffer[bytes_read] = 0;
            fprintf(LOG, "output:%s\n", buffer);
            fflush(LOG);
            bytes_written = write(client_socket, buffer, bytes_read);
            if (bytes_written <= 0) break;
        }
    }

    fclose(LOG);
    close(client_socket);
    close(master_fd);
    exit(0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pid_t pid;

    // Создаем TCP-сокет
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }

    // Настраиваем адрес сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Привязываем сокет к адресу
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(1);
    }

    // Начинаем слушать порт
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        close(server_socket);
        exit(1);
    }

    printf("Сервер слушает порт %d...\n", PORT);

    while (1) {
        // Принимаем подключение клиента
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        printf("есть подключение\n");
        // Форкаем процесс для обработки клиента
        pid = fork();
        if (pid == 0) {
            // Дочерний процесс
            close(server_socket); // Закрываем слушающий сокет в дочернем процессе
            handle_client(client_socket);
        } else if (pid > 0) {
            // Родительский процесс
            close(client_socket); // Закрываем клиентский сокет в родительском процессе
        } else {
            perror("fork");
            close(client_socket);
        }
    }

    close(server_socket);
    return 0;
}