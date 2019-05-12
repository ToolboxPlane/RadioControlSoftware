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
void joystick_load_calibration(joystick_t *joystick, uint16_t startAddr);
void joystick_start_calibration(joystick_t *joystick);
void joystick_end_calibration(joystick_t *joystick, uint16_t startAddr);
void joystick_set_x_value(joystick_t *joystick, uint16_t value);
void joystick_set_y_value(joystick_t *joystick, uint16_t value);
void joystick_set_button(joystick_t *joystick, uint16_t button);
int8_t joystick_get_x_value(const joystick_t *joystick);
int8_t joystick_get_y_value(const joystick_t *joystick);
uint8_t joystick_get_button(const joystick_t *joystick);

#endif
