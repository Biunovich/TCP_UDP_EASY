#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <error.h>
#define MSGLEN 512
#define PORT 1337
#define IPADDR "127.0.0.1"
#define CLIENT 16
#define BCASTIP "192.168.2.255"
#define MCASTIP "239.0.0.11"
