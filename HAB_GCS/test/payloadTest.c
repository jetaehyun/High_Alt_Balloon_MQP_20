#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../src/Data_Packet/header/sensor_payload.h"
#include "../src/Data_Packet/header/data_packet.h"
#include "../src/Data_Packet/header/release_payload.h"

// gcc -Wall ../src/Data_Packet/sensor_payload.c ../src/Data_Packet/data_packet.c ../src/Data_Packet/release_payload.c ../src/Data_Packet/byte_manipulation.c payloadTest.c -o test.exe

bool testReleasePack() {
    bool success = true;

    struct release_data_t *data = create_release_payload(PAYLOAD_RELEASE);

    uint8_t *payload = malloc(28);

    release_payload_pack(payload, data);
    struct release_data_t data2 = release_payload_unpack(payload);

    if(data2.confirmation != PAYLOAD_RELEASE) success = false;

    free(payload);
    free(data);

    return success;
}

bool testSensorPack() {
    bool success = true;

    struct sensor_data_t *data = create_sensor_payload(
        123456, 123456, 123456, 123456, 123456, 123456, 123456
    );


    uint8_t *payload = malloc(28);

    sensor_payload_pack(payload, data); // pack into bytes
    struct sensor_data_t data2 = sensor_payload_unpack(payload);

    if(data2.pressure_sensor != 123456  ||
        data2.NO2_sensor != 123456  ||
        data2.temp_sensor != 123456 || 
        data2.UV_sensor != 123456   ||
        data2.CO2_sensor != 123456  ||
        data2.Ozone_sensor != 123456 ||
        data2.altitude != 123456) {
            success = false;
    }

    free(payload);
    free(data);
    return success;

}

bool testChecksum() {
    bool success = true;
    uint8_t payload[] = {44, 99, 42, 221};
    uint8_t payload2[5] = {0};

    uint8_t checksum = calculate_checksum(payload, 4); 

    for(int i = 0; i < 4; i++) {
        payload2[i] = payload[i];
    }

    payload2[4] = checksum;

    if(!confirm_checksum(payload2, 5)) success = false;

    return success;
}

bool testHABPack() {
    bool success = true;

    struct sensor_data_t *data = create_sensor_payload(
        123456, 123456, 123456, 123456, 123456, 123456, 123456
    );


    uint8_t *payload = malloc(28);

    sensor_payload_pack(payload, data); // pack into bytes
    
    uint8_t *mainPayload = malloc(30);
    struct HAB_payload_t *HAB_data = HAB_payload_create(RELEASE_PAYLOAD, payload);
    struct HAB_payload_t *HAB_data2 = malloc(sizeof(struct HAB_payload_t));
    HAB_payload_pack(mainPayload, HAB_data);

    if(!HAB_payload_unpack(mainPayload, HAB_data2)) success = false;
    
    if(HAB_data2->payload_type != RELEASE_PAYLOAD) success = false;

    struct sensor_data_t sensorData = sensor_payload_unpack(HAB_data2->payload);
    if(sensorData.pressure_sensor != 123456  ||
        sensorData.NO2_sensor != 123456  ||
        sensorData.temp_sensor != 123456 || 
        sensorData.UV_sensor != 123456   ||
        sensorData.CO2_sensor != 123456  ||
        sensorData.Ozone_sensor != 123456 ||
        sensorData.altitude != 123456) {
            success = false;
    }

    free(payload);
    free(data);
    free(HAB_data);
    free(HAB_data2);

    return success;
}

bool test() {
    bool didPass = true;

    if(!testSensorPack()) {
        printf("testSensorPack() failed...\n");
        didPass = false;
    }
    if(!testReleasePack()) {
        printf("testReleasePack() failed...\n");
        didPass = false;
    }
    if(!testChecksum()) {
        printf("testChecksum() failed...\n");
        didPass = false;
    }
    if(!testHABPack()) {
        printf("testHABPack() failed...\n");
        didPass = false;
    }

    return didPass;    
    
}

int main(int argc, const char** argv) {

    if(test()) printf("All tests passed...\n");
    else       printf("Not all tests passed...\n");


    return 0;

}