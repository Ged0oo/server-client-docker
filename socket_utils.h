#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int start_server(int port);
int accept_client(int server_sock);
int connect_to_server(const char* server_ip, int port);
void handle_communication(int client_sock, bool is_server);
void send_message(int sock, const char* message);


#endif
