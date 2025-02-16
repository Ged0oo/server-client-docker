#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define SERVER_PORT 8080

int start_server(int port);
int accept_client(int server_sock);

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

        // Handle communication
        char buffer[1024];
        while (true) {
            int bytesReceived = recv(client_sock, buffer, 1024, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "Received: " << buffer << std::endl;
                
                // Send back a response
                std::string response = "Message received: ";
                response += buffer;
                send(client_sock, response.c_str(), response.length(), 0);
            } else {
                std::cout << "Client disconnected.\n";
                break;
            }
        }

        close(client_sock);
    }

    return 0;
}
