#include "udp.h"

#define PORT 8808
#define SIZE 30

int sockfd = -1;
struct sockaddr_in servaddr;

void startUDPServer(const char* ipaddr) {
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(ipaddr); 
}

void closeServer() {

    if(sockfd < 1) close(sockfd);
    else           printf("UDP Server has not started...\n");

}

size_t sendPacket(uint8_t *packet) {
    size_t dataSize = sendto(sockfd, packet, SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Bytes sent: %u\n", dataSize);

    return dataSize; 

}
