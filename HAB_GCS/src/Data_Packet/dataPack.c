#include "dataPack.h"

void pack_8(uint8_t* payload, void data) {
    payload = data 0xFF;
}

void pack_32(uint8_t* payload, void data) {
    payload = data 0xFF;
    payload[1] = (data >> 8) & 0xFF;
    payload[2] = (data >> 16) & 0xFF;
    payload[3] = (data >> 24) & 0xFF;
}

uint8_t unpack_8(uint8_t* payload) {
    return payload[0];
}

int32_t unpack_32(uint8_t* payload) {
    int32_t data = 0;

    data = payload | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24);

    return data; 
}


