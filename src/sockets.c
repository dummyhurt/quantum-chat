#include "sockets.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int create_server_socket(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) die("create_server_socket socket()\n");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        die("create_server_socket setsockopt()\n");

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        close(sockfd);
        die("create_server_socket bind()\n");
    }
    
    if(listen(sockfd, 5) < 0) {
        close(sockfd);
        die("create_server_socket listen()\n");
    }

    log("server listening at %s:%d\n", inet_ntoa(addr.sin_addr), port);
    return sockfd;
}

void server_serve(int sockfd) {
    struct sockaddr_in client_addr;
    socklen_t len_client_addr = sizeof(client_addr);
    int client_sockfd;

    client_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len_client_addr);
    if (client_sockfd < 0)
        die("server_serve accept()\n");
    
    log("%s connected\n", inet_ntoa(client_addr.sin_addr));
}

int create_client_socket(char* host, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) die("create_client_socket socket()\n");

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host);
    // socklen_t addr_len;

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        die("create_client_socket client connect()\n");

    return sockfd;
}

void send_data(int sockfd, char *data, size_t data_len) {
    int status = send(sockfd, data, data_len, 0);
    if (status < 0) die("send_data\n");
}

void receive_data(int sockfd, char *data, size_t data_len) {
    int status = read(sockfd, data, data_len);
    if (status < 0) {
        die("receive_data\n");
    } else if (status == 0) warn("EOF read\n");
}
