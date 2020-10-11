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
    int sockfd; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr); 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, '\0', sizeof(servaddr)); 
    memset(&cliaddr, '\0', sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    while(1) {
        printf("write\n");

        sendto(sockfd, hello, SIZE, 0, (struct sockaddr*)&cliaddr, len);

        sleep(1);
    }

    close(sockfd); 
   

    return 0;
}