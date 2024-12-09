#include "sockets.h"
#include "cryptography.h"
#include "protocol.h"
#include "utils.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

/*
 * This is a silly attempt to simulate Quantum TLS
 * through linux processes in which a server and
 * a client communicate thru computer gibberish
 * in a quantum fashion (could a RAT read it?)
 */

// Server process
void server() {
    int sockfd = create_server_socket(8080);
    int client_sockfd;
    struct sockaddr_in client_addr = {0};
    socklen_t addr_len;

    if ((client_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_len)) < 0)
        die("server accept()\n");

    log("%s connected\n", inet_ntoa(client_addr.sin_addr));

    char buffer[BUFSIZE] = {0};

    // Receive hello #
    receive_data(client_sockfd, buffer, BUFSIZE);
    log("received - %s\n", buffer);

    // Say hello and algs *
    server_hello(client_sockfd);   

    // Receive chosen algorithm #
    int choice = receive_selected_algorithm(client_sockfd);
    log("chosen alg = %s\n", kems[choice]);
    // Read algorithm pubkey to send to client

    // Send pubkey *

    // Read encapsulation #

    // BEGIN QUANTUM COMMUNICATIONS

    return;
}

// Client process
void client() {
    int sockfd = create_client_socket("127.0.0.1", 8080);

    char buffer[BUFSIZE];   // recv buffer

    // Say hello *
    client_hello(sockfd);

    // Receive hello #
    receive_data(sockfd, buffer, BUFSIZE);
    log("received - %s\n", buffer);

    // Separate list from header
    char **alg_list = dissect_server_algorithms(buffer);
    int n_algs = print_algorithms((const char **)alg_list);

    // Select algorithm
    int chosen_alg = menu_algorithms(n_algs);
    free_algorithm_array(alg_list);

    // Send chosen algorithm *
    send_selected_algorithm(sockfd, chosen_alg);

    // Receive sv pubkey #

    // Create secret encapuslation

    // Send encapsulation *

    // BEGIN QUANTUM COMMUNICATIONS

    return;
}

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
