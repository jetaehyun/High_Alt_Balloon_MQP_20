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

#include "Data_Packet/header/data_packet.h"
#include "Data_Packet/header/release_payload.h"
#include "Data_Packet/header/sensor_payload.h"
#include "Database/database.h"

#define PORT 8808
#define SIZE 30

int main(int argc, const char* argv[]) {

    int sockfd;
    char buffer[SIZE] = {'\0'}; 
    struct sockaddr_in servaddr; 
    socklen_t len = sizeof(servaddr);

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, '\0', sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1) {

        int size = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr *) &servaddr, &len);
        
        printf("HE\n");
        if(size > 0) {

            printf("%s\n", buffer);
        }


        sleep(1);
    }  
      
  
    close(sockfd); 

    // if(argc < 1) {
    //     printf("Enter serial port... Ex: /dev/ttyS4\n");
    //     return 0;
    // }

    // uint8_t buffer[30];
    // struct HAB_payload_t payload;

    // // find correct port
    // int descriptor = open(argv[1], O_RDONLY | O_NOCTTY);

    // if(descriptor == -1) {
    //     perror("Unable to open port...\n");
    // }

    // while(1) {

    //     int size = read(descriptor, buffer, 26);
    //     if(size > 1) {

    //         // check payload and update payload
    //         if(!HAB_payload_unpack(buffer, &payload)) continue;

    //         // unpack sensor/release payload
    //         if(payload.payload_type == SENSOR_PAYLOAD) {
    //             struct sensor_data_t sensor_payload = sensor_payload_unpack(payload.payload);
    //             // function to graph
    //         }
    //         else if(payload.payload_type == RELEASE_PAYLOAD) {
    //             struct release_data_t release_payload = release_payload_unpack(payload.payload);
    //             // confirmation 1
    //         }


    //     }

    //     sleep(5); // sleep 5s
    // }

    // close(descriptor);

    return 0;
}