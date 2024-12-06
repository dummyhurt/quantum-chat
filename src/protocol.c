#include "protocol.h"
#include "sockets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char *algorithms[] = {
    "Kyber768",
    "sntrup761",
    NULL
};

void client_hello(int sockfd) {
    char *msg = "client_hello";
    send_data(sockfd, msg, strlen(msg));
}

void server_hello(int sockfd) {
    char buffer[256] = "server_hello=";
    for (int i = 0; algorithms[i]; i++) {
        strcat(buffer, algorithms[i]);
        if (algorithms[i+1] != NULL) strcat(buffer, ",");
    }
    send_data(sockfd, buffer, strlen(buffer));
}