#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
// #include <wiringPi.h>

#define PORT 8808
#define SIZE 30

int main(int argc, const char *argv[]) {
    char buffer[100]; 
    int sockfd, n; 
    struct sockaddr_in servaddr; 
    char *message = "Hello Client"; 
  
    // clear servaddr 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
      
    // create datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
      
    // connect to server 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
  

    while(1) {
        sendto(sockfd, message, SIZE, 0, 
          (struct sockaddr*)&servaddr, sizeof(servaddr)); 
        sleep(2);
    }

    close(sockfd); 

           

    return 0;
}