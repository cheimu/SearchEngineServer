/*
 * Copyright ©2018 Gaohong Liu.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ header file declares functions that need to 
 * build connection on client side including LookupName 
 * and Connect
 */

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

// Get an appropriate sockaddr structure
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// Connect the socket to the remote host.
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

#endif  // _CONNECT_H_
