#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>
// #include <wiringPi.h>

#define PORT 1160
#define SIZE 30

int main(int argc, const char *argv[]) {
    char buffer[SIZE]; 
    int sockfd, n;
    struct sockaddr_in servaddr; 
    char *message = "Hello Client"; 
  
      // create datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset((char*)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    // servaddr.sin_port = inet_addr("192.168.0.188"); 
    servaddr.sin_port = INADDR_ANY; 

    while(1) {
        sendto(sockfd, message, strlen(message), 0, 
          (struct sockaddr*)&servaddr, sizeof(servaddr)); 
        sleep(2);
    }

    close(sockfd); 

           

    return 0;
}