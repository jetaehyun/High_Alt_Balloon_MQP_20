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