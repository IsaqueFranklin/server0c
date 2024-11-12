// #include directive is equivalent to import statement in Python
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// #define directive
#define PORT 8080
#define BUFFER_SIZE 1024

// In C => #define SQUARE(x) (x*x)
// In Python => SQUARE = lambda x : x*x

//we have the program's entry point

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  // Create socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed!");
    exit(EXIT_FAILURE);
  }

  // Set socket options
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  // Setup the server address
  // Set the address family to AF_INET(IPv4)
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;

  // Set the port number in network byte order / PORT 8080
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind fails!");
    exit(EXIT_FAILURE);
  }

  // Start listening for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listening fails!");
    exit(EXIT_FAILURE);
  }

  // Print a message indicating that the server is listening on the specific port
  printf("Server lisntening on port %d\n", PORT);

  // Accept incoming connections
  if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
    perror("Accept!");
    exit(EXIT_FAILURE);
  }

  // Accepting the connection
  printf("Connection accepted\n");

  // Read data from the client and print it
  // Declare a signed size type
  ssize_t valread;
  while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
    printf("Client: %s", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  // Close the socket
  close(server_fd);
  return 0;
}
