// 
// Server.c 
// hdelibc
//
// Created at 13/11/2024 by Isaque Franklin 
//

#include "server.h"
// The stdio lib is not imported in the 
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(struct Server *server)) {

  struct Server server;

  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;

  server.address.sin_family = domain;
  // The htons (h to networks) function converts our int port into bytes that will refer to our network port. 
  server.address.sin_port = htons(port);
  server.address.sin_addr.s_addr = htonl(interface);

  // A socket is what allows our operating system to comunicate with the network => It does it in a particular domina, using a particular type of service and a protocol.
  server.socket = socket(domain, service, protocol);
  if (server.socket == 0) {
    perror("Failed to connect socket... \n");
    exit(1);
  }

  if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
    perror("Failed to bind socket... \n");
    exit(1);
  }

  if ((listen(server.socket, server.backlog)) < 0) {
    perror("failed to start listening... \n");
    exit(1);
  }

  server.launch = launch;

  return server;
}
