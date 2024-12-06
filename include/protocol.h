#ifndef PROTO_H
#define PROTO_H

#include "utils.h"

/*
 * Send client_hello
 *
 * IN:
 *  socket filedescriptor
 */
void client_hello(int sockfd);

/*
 * Send server_hello=alg,alg,...
 *
 * IN:
 *  socket filedescriptor
 */
void server_hello(int sockfd);

/*
 * Select algorithm presented by
 * server
 * 
 * IN:
 *  list of algorithms (comma separated)
 */
void send_selected_algorithm(int sockfd, int choice);

/*
 * Receive the selected algorithm index
 *
 * IN:
 *  socket filedes
 */
int receive_selected_algorithm(int sockfd);

/*
 * Send public key associated with chosen alg
 *
 * IN:
 *  algorithm choice
 *  buffer that holds pubkey
 */
void send_pubkey(int choice, char *pubkey);

#endif