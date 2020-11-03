#ifndef RELEASE_PAYLOAD_H
#define RELEASE_PAYLOAD_H

#define PAYLOAD_RELEASE 3

#include <stdlib.h>
#include <stdint.h>

#include "byte_manipulation.h"

struct release_data_t {
    // 0
    uint8_t confirmation;
    // 1
};

struct release_data_t release_payload_unpack(uint8_t *payload);
uint8_t release_payload_pack(uint8_t *payload, struct release_data_t *data);
struct release_data_t *create_release_payload(uint8_t confirmation);

#endif