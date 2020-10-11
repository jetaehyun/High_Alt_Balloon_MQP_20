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
#define MAXLINE 1024 

int main(int argc, const char *argv[]) {
int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
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
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.156"); 
      
    int n, len; 
      
    while(1) {
        sendto(sockfd, (const char *)hello, strlen(hello), 
            0x800, (const struct sockaddr *) &servaddr,  
                sizeof(servaddr)); 
        printf("Hello message sent.\n"); 

        sleep(2);
    }  

  
    close(sockfd); 

           

    return 0;
}