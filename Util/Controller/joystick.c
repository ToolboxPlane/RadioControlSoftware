#include "joystick.h"
#include <avr/eeprom.h>
#include <stdbool.h>

#define BUTTON_SCHMITT_LOW 200
#define BUTTON_SCHMITT_HIGH 800

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

void joystick_init(joystick_t *joystick) {
    joystick->buttonState = 0;
    joystick->xVal = joystick->yVal = 0;

    joystick->isCalibrating = false;
    joystick->minX = joystick->minY = 65535;
    joystick->maxX = joystick->maxY = 0;
}

void joystick_loadConfiguration(joystick_t *joystick, uint16_t startAddr) {
    joystick->minX = eeprom_read_byte((uint8_t*)(startAddr)) *4;
    joystick->minY = eeprom_read_byte((uint8_t*)(startAddr + 1)) *4;
    joystick->maxX = eeprom_read_byte((uint8_t*)(startAddr + 2) ) *4;
    joystick->maxY = eeprom_read_byte((uint8_t*)(startAddr + 3)) *4;
}

void joystick_startCalibration(joystick_t *joystick) {
    joystick->minX = joystick->minY = 65535;
    joystick->maxX = joystick->maxY = 0;
    joystick->isCalibrating = true;
}

void joystick_endCalibration(joystick_t *joystick, uint16_t startAddr) {
    eeprom_update_byte((uint8_t*)startAddr, joystick->minX / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 1), joystick->minY / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 2), joystick->maxX / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 3), joystick->maxY / 4);
}

void joystick_setXValue(joystick_t *joystick, uint16_t value) {
    if (joystick->isCalibrating) {
        joystick->minX = min(joystick->minX, value);
        joystick->maxX = max(joystick->maxX, value);
    }
    joystick->xVal = (int8_t)((float)(value-joystick->minX)/(joystick->maxX-joystick->minX) * 254 - 127);
}

void joystick_setYValue(joystick_t *joystick, uint16_t value) {
    if (joystick->isCalibrating) {
        joystick->minY = min(joystick->minY, value);
        joystick->maxY = max(joystick->maxY, value);
    }
    joystick->yVal = (int8_t)((float)(value-joystick->minY)/(joystick->maxX-joystick->minY) * 254 - 127);
}

void joystick_setButton(joystick_t *joystick, uint16_t button) {
    if (joystick->buttonState && button < BUTTON_SCHMITT_LOW) {
        joystick->buttonState = false;
    } else if (!joystick->buttonState && button > BUTTON_SCHMITT_HIGH) {
        joystick->buttonState = true;
    }
}

int8_t joystick_getXValue(joystick_t *joystick) {
    return joystick->xVal;
}

int8_t joystick_getYValue(joystick_t *joystick) {
    return joystick->yVal;
}

uint8_t joystick_getButton(joystick_t *joystick) {
    return joystick->buttonState;
}

