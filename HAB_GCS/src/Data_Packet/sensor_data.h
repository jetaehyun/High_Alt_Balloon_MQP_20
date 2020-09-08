#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct sensor_data_t {
    // 0
    uint8_t payload_type;
    // 1
    float baro_sensor; 
    // 5
    float NO2_sensor;
    // 9
    float temp_sensor;
    // 13
    float UV_sensor;
    // 17
    float CO2_sensor;
    // 21
    float Ozone_sensor;
    // 25
}

struct release_data_t {
    // 0
    uint8_t payload_type;
    // 1
    uint8_t confirmation;
    // 2
};

enum payload_type {
    sensor_payload = 0,
    release_payload = 1
};

void unpack_payload(byte* payload);
void sensor_payload_pack(struct sensor_data_t *payload);
void release_data_pack(struct release_data_t *payload);
bool checkPayload();

#endif