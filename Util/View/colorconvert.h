#ifndef RADIOCONTROLSOFTWARE_COLORCONVERT_H
#define RADIOCONTROLSOFTWARE_COLORCONVERT_H

#include <stdint.h>

uint16_t r8g8b8Tor5g6b5(uint32_t original);
uint16_t r8g8b8Tor5g6b5_brightness(uint32_t original, uint8_t brightness);

#endif