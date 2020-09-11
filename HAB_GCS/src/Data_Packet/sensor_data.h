#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dataPack.h"

#define SENSOR_PAYLOAD
#define RELEASE_PAYLOAD

// will send 30 bytes
struct HAB_payload_t {
    // 0
    uint8_t payload_type;
    // 1
    uint8_t *payload;
    // 25
    uint8_t checksum;
    // 26
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
    uint8_t confirmation;
    // 1
};

bool HAB_unpack(uint8_t* payload, struct HAB_payload_t *data);

void HAB_payload_pack(uint8_t* payload, void *data);
uint8_t sensor_payload_pack(uint8_t *payload, struct sensor_data_t *data);
uint8_t release_data_pack(uint8_t *payload, struct release_data_t *data);

uint8_t calculate_checksum();
bool confirm_checksum(uint8_t* payload);

#endif