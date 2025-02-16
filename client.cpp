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

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0) {
        std::cout << "Connected to server!\n";

        // Send automatic messages every 2 seconds
        for (int i = 1; i <= 5; i++) {
            std::string message = "Hello " + std::to_string(i);
            send(sock, message.c_str(), message.length(), 0);
            std::cout << "Sent: " << message << std::endl;
            sleep(2);
        }
    } else {
        std::cerr << "Connection failed\n";
    }

    close(sock);
    return 0;
}
