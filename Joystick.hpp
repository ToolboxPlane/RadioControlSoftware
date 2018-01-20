#ifndef _JOYSTICK_HPP
#define _JOYSTICK_HPP

//#include "Arduino.h"
//#include "EEPROM.h"
#include <stdint.h>
#include <avr/eeprom.h>

#define BUTTON_SCHMITT_LOW 200
#define BUTTON_SCHMITT_HIGH 800

class Joystick {
public:
    Joystick();

    void loadConfiguration(uint16_t startAddr);

    void startCalibration();

    void endCalibration(uint16_t startAddr);

    void setXValue(uint16_t value);

    void setYValue(uint16_t value);

    void setButton(uint16_t button);

    int8_t getXValue();

    int8_t getYValue();

    uint8_t getButton();

    uint8_t getXChannel();

    uint8_t getYChannel();

    uint8_t getBtnChannel();

    void setXChannel(uint8_t channel);

    void setYChannel(uint8_t channel);

    void setBtnChannel(uint8_t channel);

private:
    uint8_t buttonState;
    int8_t xVal, yVal;

    uint8_t isCalibrating;
    uint16_t minX, minY, maxX, maxY;
    uint8_t xChannel, yChannel, btnChannel;
};

#endif
