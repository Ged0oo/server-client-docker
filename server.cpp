#include <iostream>
#include "socket_utils.h"

#define SERVER_PORT 8080

int main() {
    int server_sock = start_server(SERVER_PORT);
    if (server_sock < 0) {
        std::cerr << "Failed to start server\n";
        return 1;
    }

    std::cout << "Server listening on port " << SERVER_PORT << std::endl;

    while (true) {
        int client_sock = accept_client(server_sock);
        if (client_sock < 0) {
            std::cerr << "Failed to accept client\n";
            continue;
        }

        std::cout << "Client connected!\n";

        char buffer[1024];
        while (true) {
            int bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received <= 0) {
                std::cout << "Client disconnected.\n";
                close(client_sock);
                break;
            }

            buffer[bytes_received] = '\0';  // Null-terminate message
            std::cout << "Received: " << buffer << std::endl;

            // Echo message back to client
            send(client_sock, buffer, bytes_received, 0);

            // Exit condition
            if (std::string(buffer) == "exit") {
                std::cout << "Client requested disconnect.\n";
                close(client_sock);
                break;
            }
        }
    }

    return 0;
}
