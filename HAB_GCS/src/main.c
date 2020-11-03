#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sqlite3.h>
#include <sys/types.h>
#include <fcntl.h>

#include "header/data_packet.h"
#include "header/release_payload.h"
#include "header/sensor_payload.h"
#include "header/postData.h"
#include "Database/database.h"

#define PORT 8808
#define SIZE 30

//server
int main(int argc, const char* argv[]) {

    // connectWithServer();    
    // sendData(1.2,1.2,1.2,1.2,1.2,1.2,1.2);
    // closeConnection();
    

    int sockfd; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.99"); 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    // cliaddr.sin_family    = AF_INET; // IPv4 
    // cliaddr.sin_addr.s_addr = INADDR_ANY; 
    // cliaddr.sin_port = htons(PORT);  
      
    int len, n; 
  
    len = sizeof(cliaddr); 
    
    struct HAB_payload_t *HAB_data2 = malloc(sizeof(struct HAB_payload_t));
    uint8_t *mainPayload = malloc(30);
    HAB_payload_unpack(mainPayload, HAB_data2); 

    while(1) {
        n = recvfrom(sockfd, mainPayload, SIZE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
        HAB_payload_unpack(mainPayload, HAB_data2);
        struct sensor_data_t sensorData = sensor_payload_unpack(HAB_data2->payload);

        printf("buffer: %d, %d, %d, %d, %d, %d, %d\n"
        , 
        sensorData.altitude,
        sensorData.CO2_sensor,
        sensorData.NO2_sensor,
        sensorData.Ozone_sensor,
        sensorData.pressure_sensor,
        sensorData.temp_sensor,
        sensorData.UV_sensor);

        sleep(2);
    }

    return 0;
}