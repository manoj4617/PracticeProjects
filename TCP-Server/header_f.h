#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT_NUMBER 8080
#define LOCALHOST "127.0.0.1"

#define MAX_PENDING_CONNECTIONS 20
#define MAX_BUFFER_SIZE 1024
#define PORT_NUMBER 8080
#define RESP_MSG "Recieved your message:\t"