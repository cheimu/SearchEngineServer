/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declare the functions needed in network
 * connection from server side including listen and handle the connection
 * between server and client
 */

#ifndef _LISTEN_H_
#define _LISTEN_H_

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

// bind() the socket to the address(es) and port.
// Tell the socket to listen() for incoming clients
int  Listen(char *portnum, int *sock_family);

// read() and write() to that connection.
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

#endif
