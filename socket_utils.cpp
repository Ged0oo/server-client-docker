#include "socket_utils.h"

int start_server(int port) {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) return -1;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        return -1;

    if (listen(server_sock, 5) < 0)
        return -1;

    return server_sock;
}

int accept_client(int server_sock) {
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    return accept(server_sock, (struct sockaddr*)&clientAddr, &clientLen);
}

int connect_to_server(const char* server_ip, int port) {
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) return -1;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &serverAddr.sin_addr) <= 0) return -1;
    if (connect(client_sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        return -1;

    return client_sock;
}

void handle_communication(int client_sock, bool is_server) {
    char buffer[1024];
    int bytes = read(client_sock, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
    close(client_sock);
}

void send_message(int sock, const char* message) {
    send(sock, message, strlen(message), 0);
}
