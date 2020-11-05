#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>

#include "Data_Packet/data_packet.h"
#include "Data_Packet/release_payload.h"
#include "Data_Packet/sensor_payload.h"
#include "Database/database.h"

#include <wiringPi.h>
#include <wiringSerial.h>

#define PORT 8808
#define SIZE 30

// will need to compile with: sudo ./gcs.exe

int main(int argc, const char *argv[]) {

    // int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_SYNC);

    // if(fd < 0) {
    //     fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    //     return 0;
    // }

    // uint8_t *incoming_sensor_data = malloc(sizeof(uint8_t) * SIZE);
    // uint8_t *check_sensor_data = malloc(sizeof(uint8_t) * 28);
    // struct HAB_payload_t *habData = malloc(sizeof(struct HAB_payload_t));

    // while(1) {
    //     size_t data = read(fd, incoming_sensor_data, SIZE);
    //     printf("%d\n", data);

    //     // if(data >= SIZE) {
    //     HAB_payload_unpack(incoming_sensor_data, habData);
    //     printf("TYPE: %d\n", habData->payload_type); 
    //     struct sensor_data_t w = sensor_payload_unpack(habData->payload);
    //     printf("%d, %d, %d, %d, %d, %d, %d\n", w.altitude, w.CO2_sensor, w.NO2_sensor, w.Ozone_sensor, w.pressure_sensor, w.temp_sensor, w.UV_sensor);
            

    //     // }
    //     sleep(2);
    // }

    int fd = serialOpen("/dev/ttyS0", 9600);

    if(fd < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 0;
    }

    uint8_t *incoming_sensor_data = malloc(sizeof(uint8_t) * SIZE);
    uint8_t *check_sensor_data = malloc(sizeof(uint8_t) * 28);
    struct HAB_payload_t *habData = malloc(sizeof(struct HAB_payload_t));

    while(1) {
        int data = serialDataAvail(fd);
        printf("%d\n", data);

        if(data >= SIZE) {
        for(int i = 0; i < SIZE; i++) {
            incoming_sensor_data[i] = (uint8_t)serialGetchar(fd);
        }
        HAB_payload_unpack(incoming_sensor_data, habData);
        printf("TYPE: %d\n", habData->payload_type); 
        struct sensor_data_t w = sensor_payload_unpack(habData->payload);
        printf("%d, %d, %d, %d, %d, %d, %d\n", w.altitude, w.CO2_sensor, w.NO2_sensor, w.Ozone_sensor, w.pressure_sensor, w.temp_sensor, w.UV_sensor);
            

        }
        sleep(2);
    }



    // int sockfd; 

    // struct sockaddr_in     servaddr; 
  
    // // Creating socket file descriptor 
    // if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
    //     perror("socket creation failed"); 
    //     exit(EXIT_FAILURE); 
    // } 
  
    // memset(&servaddr, 0, sizeof(servaddr)); 
      
    // // Filling server information 
    // servaddr.sin_family = AF_INET; 
    // servaddr.sin_port = htons(PORT); 
    // servaddr.sin_addr.s_addr = inet_addr("192.168.1.99"); 
      
    // int n, len; 

    // struct sensor_data_t *data = create_sensor_payload(
    //     123456, 123456, 123456, 123456, 123456, 123456, 123456
    // );


    // uint8_t *payload = malloc(SIZE);

    // sensor_payload_pack(payload, data); // pack into bytes
    
    // uint8_t *mainPayload = malloc(SIZE);
    // struct HAB_payload_t *HAB_data = HAB_payload_create(SENSOR_PAYLOAD, payload);
    // HAB_payload_pack(mainPayload, HAB_data);
      
    // while(1) {
    //     printf("%u\n",sendto(sockfd, mainPayload, SIZE, 
    //         MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
    //             sizeof(servaddr))); 
    //     printf("Sensor data sent.\n"); 

    //     sleep(2);
    // }  

  
    // close(sockfd); 
    close(fd);
    free(incoming_sensor_data);
           

    return 0;
}
