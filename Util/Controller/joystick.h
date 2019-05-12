#ifndef _JOYSTICK_HPP
#define _JOYSTICK_HPP

#include <stdint.h>

typedef struct {
    uint8_t buttonState;
    int8_t xVal, yVal;
    uint8_t isCalibrating;
    uint16_t minX, minY, maxX, maxY;
} joystick_t;

void joystick_init(joystick_t *joystick);
void joystick_loadConfiguration(joystick_t *joystick, uint16_t startAddr);
void joystick_startCalibration(joystick_t *joystick);
void joystick_endCalibration(joystick_t *joystick, uint16_t startAddr);
void joystick_setXValue(joystick_t *joystick, uint16_t value);
void joystick_setYValue(joystick_t *joystick, uint16_t value);
void joystick_setButton(joystick_t *joystick, uint16_t button);
int8_t joystick_getXValue(joystick_t *joystick);
int8_t joystick_getYValue(joystick_t *joystick);
uint8_t joystick_getButton(joystick_t *joystick);

#endif
