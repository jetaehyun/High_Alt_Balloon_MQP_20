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

#define PORT 1160
#define MAXLINE 1024 

//server
int main(int argc, const char* argv[]) {

    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
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
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.156"); 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    cliaddr.sin_family    = AF_INET; // IPv4 
    cliaddr.sin_addr.s_addr = INADDR_ANY; 
    cliaddr.sin_port = htons(PORT);  
      
    int len, n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
  
    while(1) {
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("buffer: %s\n", buffer);
        sleep(2);
    }



    // char buffer[SIZE] = {'\0'}; 
    // char *message = "Hello Client"; 
    // int listenfd, len; 
    // struct sockaddr_in servaddr, cliaddr; 
  
    // // Create a UDP Socket 
    // if((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    //     perror("Couldn't create socket\n");
    //     return 0;
    // }

    // memset((char *)&servaddr, 0, sizeof(servaddr));

    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    // // servaddr.sin_addr.s_addr = inet_addr("192.168.0.188"); 
    // servaddr.sin_port = htons(PORT); 
    // servaddr.sin_family = AF_INET; 

    // // cliaddr.sin_addr.s_addr = inet_addr("192.168.0.188"); 
    // // cliaddr.sin_port = htons(PORT); 
    // // cliaddr.sin_family = AF_INET; 
 
   
    // // bind server address to socket descriptor 
    // if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    //     perror("Failed to bind socket");
    //     exit(EXIT_FAILURE);
    // } 
       

    // while(1) {
    
    //     int some = recvfrom(listenfd, buffer, SIZE, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    //     if(some > 0) {
    //         buffer[some] = '\0';
    //         printf("%d\n", some);
    //     }
    //     // puts(some);   
        

    //     sleep(2);      
    // }  

    // close(listenfd);


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