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
#include <signal.h>

#include "header/data_packet.h"
#include "header/release_payload.h"
#include "header/sensor_payload.h"
#include "header/postData.h"
#include "Database/database.h"

#define PORT 8808
#define SIZE 30

static volatile bool gatherData = true;

void sigint_handler(int signum) {
    gatherData = false;
}

//server
int main(int argc, const char* argv[]) {

    signal(SIGINT, sigint_handler);

    // connectWithServer();
    // startDB();    
    

    int sockfd; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    // servaddr.sin_addr.s_addr = inet_addr("192.168.1.99"); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    socklen_t len = sizeof(cliaddr); 
    int n; 
    
    struct HAB_payload_t *HAB_data = malloc(sizeof(struct HAB_payload_t));
    uint8_t *mainPayload = malloc(SIZE);

    while(gatherData) {
        n = recvfrom(sockfd, mainPayload, SIZE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len); // this is blocking
        HAB_payload_unpack(mainPayload, HAB_data);
        struct sensor_data_t sensorData = sensor_payload_unpack(HAB_data->payload);
        // sendData(1.2,1.2,1.2,1.2,1.2,1.2,1.2);
        // insertDatabase();

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

    free(mainPayload);
    free(HAB_data);
    // closeConnection();
    // closeDB();


    return 0;
}