#include "Joystick.hpp"

Joystick::Joystick() {
    buttonState = 0;
    xVal = yVal = 0;

    isCalibrating = false;
    minX = minY = 1023;
    maxX = maxY = 0;
}

void Joystick::loadConfiguration(uint16_t startAddr) {
    minX = EEPROM.read(startAddr) * 4;
    minY = EEPROM.read(startAddr + 1) * 4;
    maxX = EEPROM.read(startAddr + 2) * 4;
    maxY = EEPROM.read(startAddr + 3) * 4;
}

void Joystick::startCalibration() {
    minX = minY = maxX = maxY = 512;
    isCalibrating = true;
}

void Joystick::endCalibration(uint16_t startAddr) {
    EEPROM.write(startAddr, minX / 4);
    EEPROM.write(startAddr + 1, minY / 4);
    EEPROM.write(startAddr + 2, maxX / 4);
    EEPROM.write(startAddr + 3, maxY / 4);
}

void Joystick::setXValue(uint16_t value) {
    if (isCalibrating) {
        minX = min(minX, value);
        maxX = max(maxX, value);
    }
    xVal = map(value, minX, maxX, -127, 127);
}

void Joystick::setYValue(uint16_t value) {
    if (isCalibrating) {
        minY = min(minY, value);
        maxY = max(maxY, value);
    }
    yVal = map(value, minY, maxY, -127, 127);
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