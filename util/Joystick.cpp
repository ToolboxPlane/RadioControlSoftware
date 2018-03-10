#include "Joystick.hpp"

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

Joystick::Joystick() {
    buttonState = 0;
    xVal = yVal = 0;

    isCalibrating = false;
    minX = minY = 1023;
    maxX = maxY = 0;
}

void Joystick::loadConfiguration(uint16_t startAddr) {
    minX = eeprom_read_byte((uint8_t*)(startAddr)) *4;
    minY = eeprom_read_byte((uint8_t*)(startAddr + 1)) *4;
    maxX = eeprom_read_byte((uint8_t*)(startAddr + 2) ) *4;
    maxY = eeprom_read_byte((uint8_t*)(startAddr + 3)) *4;
}

void Joystick::startCalibration() {
    minX = minY = maxX = maxY = 512;
    isCalibrating = true;
}

void Joystick::endCalibration(uint16_t startAddr) {
    eeprom_update_byte((uint8_t*)startAddr, minX / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 1), minY / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 2), maxX / 4);
    eeprom_update_byte((uint8_t*)(startAddr + 3), maxY / 4);
}

void Joystick::setXValue(uint16_t value) {
    if (isCalibrating) {
        minX = min(minX, value);
        maxX = max(maxX, value);
    }
    xVal = (int8_t)((float)(value-minX)/(maxX-minX) * 254 - 127);
}

void Joystick::setYValue(uint16_t value) {
    if (isCalibrating) {
        minY = min(minY, value);
        maxY = max(maxY, value);
    }
    yVal = (int8_t)((float)(value-minY)/(maxX-minY) * 254 - 127);
}

void Joystick::setButton(uint16_t button) {
    if (buttonState && button < BUTTON_SCHMITT_LOW) {
        buttonState = false;
    } else if (!buttonState && button > BUTTON_SCHMITT_HIGH) {
        buttonState = true;
    }
}

int8_t Joystick::getXValue() {
    return xVal;
}

int8_t Joystick::getYValue() {
    return yVal;
}

uint8_t Joystick::getButton() {
    return buttonState;
}

uint8_t Joystick::getXChannel() {
    return xChannel;
}

uint8_t Joystick::getYChannel() {
    return yChannel;
}

uint8_t Joystick::getBtnChannel() {
    return btnChannel;
}

void Joystick::setXChannel(uint8_t channel) {
    xChannel = channel;
}

void Joystick::setYChannel(uint8_t channel) {
    yChannel = channel;
}

void Joystick::setBtnChannel(uint8_t channel) {
    btnChannel = channel;
}