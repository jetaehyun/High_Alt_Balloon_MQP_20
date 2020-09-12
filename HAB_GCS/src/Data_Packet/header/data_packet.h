#ifndef DATA_PACKET_H
#define DATA_PACKET_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "byte_manipulation.h"

#define SENSOR_PAYLOAD 1 
#define RELEASE_PAYLOAD 2

// will send 30 bytes
struct HAB_payload_t {
    // 0
    uint8_t payload_type;
    // 1
    uint8_t *payload; // max 24 bytes
    // 2
    uint8_t checksum;
    // 3
};


bool HAB_payload_unpack(uint8_t *payload, struct HAB_payload_t *data);
uint8_t HAB_payload_pack(uint8_t *payload, struct HAB_payload_t *message);


uint8_t calculate_checksum();
bool confirm_checksum(uint8_t* payload);

#endif