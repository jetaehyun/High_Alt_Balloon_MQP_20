#include "postData.h"

#define PORT 80
#define API_KEY ""

struct hostent *server = NULL;
struct sockaddr_in server_addr;
int sockfd = 0;

const char *host = "api.thingspeak.com";
char *request = "POST /update?"
                "api_key=%s"
                "&field1=%f"
                "&field2=%f"
                "&field3=%f"
                "&field4=%f"
                "&field5=%f"
                "&field6=%f"
                "&field7=%f"
                " HTTP/1.0\r\n\r\n";

void sendData(float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude) {
    if(server == NULL) {
        printf("No connection to server...\n");
        return;
    }

    int bytes = 0;
    char buffer[1024] = {'\0'};
    char buffer2[1024] = {'\0'};
    sprintf(buffer, request, API_KEY, pressure_sensor, NO2_sensor, temp_sensor, UV_sensor, CO2_sensor, Ozone_sensor, altitude);

    bytes = write(sockfd, buffer, sizeof(buffer));
    printf("Number of bytes: %d\n", bytes);
    puts(buffer);

    read(sockfd, buffer2, sizeof(buffer2));
    puts(buffer2);

}

bool connectWithServer() {

    if(server != NULL) {
        printf("Is it already connected?\n");
        return false;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) {
        printf("Failed to create socket for ThingSpeak\n");
        return false;
    }


    server = gethostbyname(host);

    if(server == NULL) {
        printf("Server does not exist...\n");
        return false;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Could not connect to server...\n");
        return false;
    }


    return true;

}

void closeConnection() {
    close(sockfd);
    server = NULL;
}
