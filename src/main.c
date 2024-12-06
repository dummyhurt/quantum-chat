#include "sockets.h"
#include "protocol.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

void server() {
    int sockfd = create_server_socket(8080);
    int client_sockfd;
    struct sockaddr_in client_addr = {0};
    socklen_t addr_len;

    if ((client_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_len)) < 0)
        die("server accept()\n");

    log("%s connected\n", inet_ntoa(client_addr.sin_addr));

    char buffer[BUFSIZE] = {0};

    // Receive hello
    receive_data(client_sockfd, buffer, BUFSIZE);
    log("received - %s\n", buffer);

    // Say hello
    server_hello(client_sockfd);   

    return;
}

void client() {
    int sockfd = create_client_socket("127.0.0.1", 8080);

    char buffer[BUFSIZE];

    // Say hello
    client_hello(sockfd);

    // Receive hello
    receive_data(sockfd, buffer, BUFSIZE);
    log("received - %s\n", buffer);

    return;
}

// main
int main() {
    pid_t pid = fork();
    switch(pid) {
    case -1:
        die("fork() error\n");
        break;
    case 0:
        log("Child process spawned - server\n");
        server();
        break;
    default:
        log("Parent process - client\n");
        sleep(2);
        client();
        break;
    }

    return 0;
}