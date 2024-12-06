#ifndef SOCKETS_H
#define SOCKETS_H

#include "utils.h"

/*
 * Creates a server socket
 *
 * IN:
 *  port to listen on
 * 
 * RETURNS:
 *  server socketfd
 */
int create_server_socket(int port);

/*
 * Serving routine
 *
 * IN:
 *  socket file descriptor
 */
void server_serve(int sockfd);

/*
 * Creates a client socket
 *
 * IN:
 *  port to connect to
 *
 * RETURNS:
 *  client socketfd
 */
int create_client_socket(char *host, int port);

/*
 * Sends data
 *
 * IN:
 *  sock file descriptor
 *  data buffer
 *  data_len #bytes to send
 */
void send_data(int sockfd, char *data, size_t data_len);

/*
 * Receives data
 * 
 * IN:
 *  sock file descriptor
 *  data buffer
 *  data_len #bytes to read
 */
void receive_data(int sockfd, char *data, size_t data_len);

#endif