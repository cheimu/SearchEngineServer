/*
 * Copyright ©2018 Gaohong Liu and cse333-staff.
 * Name: Gaohong Liu
 * Student#: 1561226
 * Email: gaohol@uw.edu
 * 
 * This C++ program implement connection to server 
 */

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include "./connect.h"

bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen) {
  struct addrinfo hints, *results;
  int retval;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup by invoking getaddrinfo().
  if ((retval = getaddrinfo(name, nullptr, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }

  // Set the port in the first result.
  if (results->ai_family == AF_INET) {
    // v4
    struct sockaddr_in *v4addr = (struct sockaddr_in *) results->ai_addr;
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    // v6
    struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) results->ai_addr;
    v6addr->sin6_port = htons(port);
  } else {
    // error
    std::cerr << "getaddrinfo failed to provide an IPv4 or IPv6 address";
    std::cerr << std::endl;
    freeaddrinfo(results);
    return false;
  }

  // Return the first result.
  assert(results != nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;

  // Clean up.
  freeaddrinfo(results);
  return true;
}

bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd) {
  // Create the socket.
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }

  // Connect the socket to the remote host.
  int res = connect(socket_fd,
                    reinterpret_cast<const struct sockaddr *>(&addr),
                    addrlen);
  if (res == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    return false;
  }

  *ret_fd = socket_fd;
  return true;
}