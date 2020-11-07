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
#include <signal.h>

#include "Data_Packet/data_packet.h"
#include "Data_Packet/release_payload.h"
#include "Data_Packet/sensor_payload.h"
#include "Database/database.h"
// #include "udp.h"


#include <wiringPi.h>
#include <wiringSerial.h>

#define PORT 8808
#define SIZE 30
#define MAX_ALTITUDE 90000.0

// will need to compile with: sudo ./gcs.exe

static volatile bool gatherData = true;

void sigint_handler(int signum) {
	gatherData = false;

}

int main(int argc, const char *argv[]) {
	signal(SIGINT, sigint_handler);
	
    int fd = serialOpen("/dev/ttyACM0", 9600);
    //int fd = serialOpen("/dev/ttyUSB0", 9600);

    // int fd = serialOpen("/dev/ttyS0", 9600);
    
	
    startDB();
    if(fd < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 0;
    }

    uint8_t *incoming_sensor_data = malloc(SIZE);
    struct HAB_payload_t *habData = malloc(sizeof(struct HAB_payload_t));


     int sockfd; 

     struct sockaddr_in     servaddr; 
  
     // Creating socket file descriptor 
     if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
          perror("socket creation failed"); 
          exit(EXIT_FAILURE); 
     } 
  
     memset(&servaddr, 0, sizeof(servaddr)); 
      
  //   // Filling server information 
     servaddr.sin_family = AF_INET; 
     servaddr.sin_port = htons(PORT); 
     servaddr.sin_addr.s_addr = inet_addr("192.168.1.99"); 
            
     while(gatherData) {
       int data = serialDataAvail(fd);
       printf("data: %d\n", data);
       if(data >= SIZE) {
          for(int i = 0; i < SIZE; i++) {
            incoming_sensor_data[i] = (uint8_t)serialGetchar(fd);
	        }

          HAB_payload_unpack(incoming_sensor_data, habData);
          struct sensor_data_t w = sensor_payload_unpack(habData->payload);

	        float alt = (float) w.altitude / 1000;
	        float co2 = (float) w.CO2_sensor / 1000;
	        float no2 = (float) w.NO2_sensor / 1000;
	        float ozone = (float) w.Ozone_sensor / 1000;
	        float pres = (float) w.pressure_sensor / 1000;
	        float temp = (float) w.temp_sensor / 1000;
	        float uv =  (float) w.UV_sensor / 1000;

          printf("%f, %f, %f, %f, %f, %f, %f\n", alt, co2, no2, ozone, pres, temp, uv);

	        insertDatabase(pres, no2, temp, uv, co2, ozone, alt);

		
       	  printf("%u\n",sendto(sockfd, incoming_sensor_data, SIZE, 
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr))); 
         	printf("Sensor data sent.\n"); 


          serialFlush(fd);
	      }

         sleep(5);
     }  

  
    // closeServer();
    closeDB();
    close(fd);
    free(habData);
    free(incoming_sensor_data);
           

    return 0;
}
