#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../src/Data_Packet/header/sensor_payload.h"
#include "../src/Data_Packet/header/data_packet.h"
#include "../src/Data_Packet/header/release_payload.h"

// gcc -Wall ../src/Data_Packet/sensor_payload.c ../src/Data_Packet/data_packet.c ../src/Data_Packet/release_payload.c ../src/Data_Packet/byte_manipulation.c payloadTest.c -o test.exe

bool testReleasePack() {
    struct release_data_t *data = create_release_payload(PAYLOAD_RELEASE);

    uint8_t *payload = malloc(24);

    release_payload_pack(payload, data);
    struct release_data_t data2 = release_payload_unpack(payload);

    if(data2.confirmation != PAYLOAD_RELEASE) return false;

    return true;
}

bool testSensorPack() {
    struct sensor_data_t *data = create_sensor_payload(
        123456, 123456, 123456, 123456, 123456, 123456
    );


    uint8_t *payload = malloc(24);

    sensor_payload_pack(payload, data); // pack into bytes
    struct sensor_data_t data2 = sensor_payload_unpack(payload);

    if(data2.baro_sensor != 123456  ||
        data2.NO2_sensor != 123456  ||
        data2.temp_sensor != 123456 || 
        data2.UV_sensor != 123456   ||
        data2.CO2_sensor != 123456  ||
        data2.Ozone_sensor != 123456) {
        return false;
    }

    return true;

}

bool test() {
    if(!testSensorPack()) {
        printf("testSensorPack() failed!\n");
        return false;
    } else if(!testReleasePack()) {
        printf("testReleasePack() failed!\n");
        return false;
    }

    return true;    
    
}

int main(int argc, const char** argv) {

    if(test()) printf("All tests passed...\n");
    else       printf("Not all tests passed...\n");


    return 0;

}