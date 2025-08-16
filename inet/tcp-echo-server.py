import socket
import select

HOST = "0.0.0.0"
PORT = 12345
MAX_CLIENTS = 5

def main():
    # создаём TCP-сокет
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_sock.bind((HOST, PORT))
    server_sock.listen(MAX_CLIENTS)
    server_sock.setblocking(False)

    # список отслеживаемых сокетов
    sockets = [server_sock]
    clients = {}

    print(f"Echo-сервер запущен на {HOST}:{PORT}")

    while True:
        readable, writable, errored = select.select(sockets, [], sockets)

        for sock in readable:
            if sock is server_sock:
                # новое подключение
                client_sock, addr = server_sock.accept()
                if len(clients) >= MAX_CLIENTS:
                    print(f"Отклонено соединение от {addr}, достигнут лимит {MAX_CLIENTS}")
                    client_sock.close()
                else:
                    print(f"Подключен клиент {addr}")
                    client_sock.setblocking(False)
                    sockets.append(client_sock)
                    clients[client_sock] = addr
            else:
                # данные от клиента
                try:
                    data = sock.recv(1024)
                    if data:
                        print(f"От {clients[sock]}: {data.decode(errors='ignore')}")
                        sock.sendall(data)  # отсылаем обратно
                    else:
                        # клиент закрыл соединение
                        print(f"Отключен клиент {clients[sock]}")
                        sockets.remove(sock)
                        del clients[sock]
                        sock.close()
                except ConnectionResetError:
                    print(f"Клиент {clients[sock]} принудительно разорвал соединение")
                    sockets.remove(sock)
                    del clients[sock]
                    sock.close()

        for sock in errored:
            if sock in clients:
                print(f"Ошибка на сокете {clients[sock]}")
                sockets.remove(sock)
                del clients[sock]
                sock.close()

if __name__ == "__main__":
    main()
