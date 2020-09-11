#ifndef DATAPACK_H
#define DATAPACK_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void pack_8(uint8_t* payload);
void pack_32(uint8_t* payload);
uint8_t unpack_8(uint8_t* payload);
int32_t unpack_32(uint8_t* payload);

#endif