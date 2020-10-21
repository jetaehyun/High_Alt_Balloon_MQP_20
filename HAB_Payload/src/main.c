#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>

#include "Data_Packet/header/data_packet.h"
#include "Data_Packet/header/release_payload.h"
#include "Data_Packet/header/sensor_payload.h"
#include "Database/database.h"

// #include <wiringPi.h>

#define PORT 1160
#define SIZE 30 

int main(int argc, const char *argv[]) {
    int sockfd; 
    uint8_t buffer[SIZE]; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.99"); 
      
    int n, len; 

    struct sensor_data_t *data = create_sensor_payload(
        123456, 123456, 123456, 123456, 123456, 123456, 123456
    );


    uint8_t *payload = malloc(28);
    sensor_payload_pack(payload, data); 
    
    uint8_t *mainPayload = malloc(30);
    struct HAB_payload_t *HAB_data = HAB_payload_create(RELEASE_PAYLOAD, payload);
    HAB_payload_pack(mainPayload, HAB_data);
      
    while(1) {
        sendto(sockfd, mainPayload, strlen(hello), 
            0x800, (const struct sockaddr *) &servaddr,  
                sizeof(servaddr)); 
        printf("Hello message sent.\n"); 

        sleep(2);
    }  

  
    close(sockfd); 

           

    return 0;
}