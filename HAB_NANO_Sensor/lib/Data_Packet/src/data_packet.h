#ifndef DATA_PACKET_H
#define DATA_PACKET_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "byte_manipulation.h"

#define SENSOR_PAYLOAD 1 
#define RELEASE_PAYLOAD 2

// will send 26 bytes
struct HAB_payload_t {
    // 0
    uint8_t payload_type;
    // 1
    uint8_t payload[28]; // max 28 bytes
    // 2
    uint8_t checksum;
    // 3
};

struct HAB_payload_t *HAB_payload_create(uint8_t payload_type, uint8_t *payload);
bool HAB_payload_unpack(uint8_t *payload, struct HAB_payload_t *data);
uint8_t HAB_payload_pack(uint8_t *payload, struct HAB_payload_t *data);


uint8_t calculate_checksum(uint8_t *payload, int size);
bool confirm_checksum(uint8_t *payload, int size);


#ifdef __cplusplus
}
#endif


#endif