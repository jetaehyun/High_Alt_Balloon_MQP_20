#include "header/byte_manipulation.h"

// MUST FIND OUT ENDIANESS OF THE UCONTROLLERS

/**
 * @brief packs 8 bits
 * 
 * @param payload byte array to store into
 * @param data data to be stored
 */
void pack_8(uint8_t* payload, uint8_t data) {
    payload[0] = data & 0xFF;
}

/**
 * @brief packs 32 bits
 * 
 * @param payload byte array to store into
 * @param data data to be stored
 */
void pack_32(uint8_t* payload, int32_t data) {
    payload[0] = data & 0xFF;
    payload[1] = (data >> 8) & 0xFF;
    payload[2] = (data >> 16) & 0xFF;
    payload[3] = (data >> 24) & 0xFF;
}

/**
 * @brief unpacks 8 bits
 * 
 * @param payload byte array to unpack
 * @return uint8_t returns value
 */
uint8_t unpack_8(uint8_t* payload) {
    return payload[0];
}

/**
 * @brief unpacks 32 bits
 * 
 * @param payload byte array to unpack
 * @return int32_t returns combined 32 bit variable
 */
int32_t unpack_32(uint8_t* payload) {
    int32_t data = 0;

    data = payload[0] | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24);

    return data; 
}


