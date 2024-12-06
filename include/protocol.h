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

#endif