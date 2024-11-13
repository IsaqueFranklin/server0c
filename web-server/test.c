#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void launch(struct Server *server) {

  char buffer[30000];

  printf("==== WAITING FOR CONNECTION ==== \n");

  int address_length = sizeof(server.address);
  int new_socket = accept(server.socket, struct(sockaddr *)&server.address, (socklen_t *)&address_length);
  read(new_socket, buffer, 30000);

  printf("%s\n", buffer);
  char *hello = "HTTP/1.1 200 OK\nDate: Wed, 13 Nov 2024 12:28:63 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Web, 13 Nov 2024 19:15:56 GMT\nContent_Length: 88\nContent-Type: text/html\nConnection: Closed\n<html><body>Mh1>Stuff</h1>M</body></html>";
  write(new_socket, hello, strlen(hello));

  close(new_socket);
}

int main() {
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
}
