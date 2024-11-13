//
// Server_h
// hdelibc
//
// Created by Isaque Franklin at 12/11/2024.
//

#ifdef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server {
  int domain;
  int protocol;
  int service;
  u_long interface;
  int port;
  int backlog;

  struct sockaddr_in address;

  int socket;

  void (*launch)(void);
};

// This is a function prototype in which we define a function with all of its parameters whithout instantiating it. => To organize file and reference them. => and to be clean.
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(void));

#endif /* Server_h */
