#ifndef UDP_H
#define UDP_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>

void startUDPServer(const char* ipaddr);
void closeServer();
size_t sendPacket(uint8_t *packet);

#endif