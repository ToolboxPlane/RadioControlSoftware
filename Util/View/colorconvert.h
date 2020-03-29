#ifndef RADIOCONTROLSOFTWARE_COLORCONVERT_H
#define RADIOCONTROLSOFTWARE_COLORCONVERT_H

#include <stdint.h>

uint16_t r8g8b8_to_r5g6b5(uint32_t original);

#define _R8G8B8_TO_R5G6B5(original) ((uint16_t)(0x1F & ((original) >> 19)) << 11 | \
    (uint16_t)(0x3F & ((original) >> 10)) << 5 | (uint16_t)(0x1F & ((original) >> 3)))

#define R8G8B8_TO_R5G6B5(original) _R8G8B8_TO_R5G6B5((uint32_t)(original))

#endif
