#ifndef SENSOR_PAYLOAD_H
#define SENSOR_PAYLOAD_H

#include <stdlib.h>
#include <stdint.h>

#include "byte_manipulation.h"

struct sensor_data_t {
    // 0
    int32_t pressure_sensor; 
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
    int32_t altitude;
    // 28
};

struct sensor_data_t sensor_payload_unpack(uint8_t *payload);
uint8_t sensor_payload_pack(uint8_t *payload, struct sensor_data_t *data);
struct sensor_data_t *create_sensor_payload(int32_t pressure_sensor, int32_t NO2_sensor, int32_t temp_sensor, int32_t UV_sensor, int32_t CO2_sensor, int32_t Ozone_sensor, int32_t altitude);

#endif