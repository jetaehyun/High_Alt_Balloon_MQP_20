#ifndef BYTE_MANIPULATION_H
#define BYTE_MANIPULATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

void pack_8(uint8_t* payload, uint8_t data);
void pack_32(uint8_t* payload, int32_t data);
uint8_t unpack_8(uint8_t* payload);
int32_t unpack_32(uint8_t* payload);

#ifdef __cplusplus
}
#endif


#endif