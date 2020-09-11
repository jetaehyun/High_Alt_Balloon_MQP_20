#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// will send 30 bytes
struct HAB_payload_t {
    // 0
    uint8_t payload_type;
    // 1
    uint8_t *payload;
    // 2
    uint8_t checksum;
    // 3
};

struct sensor_data_t {
    // 0
    int32_t baro_sensor; 
    // 4
    int32_t NO2_sensor;
    // 8
    int32_t temp_sensor;
    // 12
    int32_t UV_sensor;
    // 16
    int32_t CO2_sensor;
    // 20
    int32_t Ozone_sensor;
    // 24
};

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

void unpack_payload(uint8_t* payload);
void sensor_payload_pack(struct sensor_data_t *payload);
void release_data_pack(struct release_data_t *payload);
bool checkPayload();
int calculate_checksum();
bool confirm_checksum();

#endif