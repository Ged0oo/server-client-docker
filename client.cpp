#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

#define SERVER_IP "cpp_server"
#define SERVER_PORT 8080

int main() {
    int sock;
    struct sockaddr_in serverAddr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    struct hostent* server = gethostbyname(SERVER_IP);
    if (!server) {
        std::cerr << "Error: Host resolution failed\n";
        return 1;
    }
    std::memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    for (int i = 0; i < 10; i++) {
        if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0) {
            std::cout << "Connected to server!\n";

            std::string msg;
            char buffer[1024];

            while (true) {
                std::cout << "Enter message: ";
                std::getline(std::cin, msg);

                send(sock, msg.c_str(), msg.size(), 0);

                if (msg == "exit") break;

                int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
                if (bytes_received <= 0) break;

                buffer[bytes_received] = '\0';
                std::cout << "Server: " << buffer << std::endl;
            }

            break;
        }
        std::cerr << "Connection failed. Retrying...\n";
        sleep(2);
    }

    close(sock);
    return 0;
}
