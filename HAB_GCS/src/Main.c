#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <fcntl.h>

#include "Data_Packet/header/data_packet.h"
#include "Data_Packet/header/release_payload.h"
#include "Data_Packet/header/sensor_payload.h"
#include "Database/database.h"

int main(int argc, const char* argv[]) {

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