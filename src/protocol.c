#include "protocol.h"
#include "sockets.h"
#include "cryptography.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char *algorithms[] = {
    "Kyber768",
    "sntrup761",
    NULL
};

extern const int ciphertext_lens[];
extern const int pubkey_lens[];
extern const int sharedsecret_lens[];

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

void send_selected_algorithm(int sockfd, int choice) {
    char buffer[256];
    snprintf(buffer, 256, "client_chose=%d", choice);
    send_data(sockfd, buffer, strlen(buffer));
}

int receive_selected_algorithm(int sockfd) {
    char buffer[256];
    receive_data(sockfd, buffer, 256);
    char *chosen_alg = strtok(buffer, "=");
    chosen_alg = strtok(NULL, "=");
    int choice = atoi(chosen_alg);  // WARNING
    return choice;
}

void send_pubkey(int sockfd, Keypair *kp) {
    char buffer[2048];
    snprintf(buffer, 2048, "PU=%s", (char*)kp->pubkey);
    send_data(sockfd, buffer, strlen(buffer));
}

uint8_t *receive_pubkey(int sockfd, int choice) {
    char buffer[2048];
    receive_data(sockfd, buffer, 2048);
    char *pk = strtok(buffer, "=");
    pk = strtok(NULL, "=");
    uint8_t *pubkey = (uint8_t*) malloc(sizeof(uint8_t) * pubkey_lens[choice]);
    snprintf((char*) pubkey, pubkey_lens[choice], "%s", pk);
    return pubkey;
}
