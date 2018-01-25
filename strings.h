//
// Created by paul on 20.01.18.
//

#ifndef RADIOCONTROLSOFTWARE_STRINGS_H
#define RADIOCONTROLSOFTWARE_STRINGS_H

#include <avr/pgmspace.h>

#define F(x) getData(x),12

namespace strings {
    static const char back[] PROGMEM = "Back";
    static const char armDisarm[] PROGMEM = "Arm/Disarm";
    static const char flightmodes[] PROGMEM = "Flightmodes";
    static const char downlink[] PROGMEM = "Downlink";
    static const char channelMapping[] PROGMEM = "Channel Map";
    static const char settings[] PROGMEM = "Settings";
    static const char debug[] PROGMEM = "Debug";
    static const char move[] PROGMEM = "Move";
    static const char the[] PROGMEM = "the";
    static const char joysticks[] PROGMEM = "Joysticks";
    static const char button[] PROGMEM = "Button";
    static const char finish[] PROGMEM = "Finish";
    static const char calibrate[] PROGMEM = "Calibrate";
    static const char disableUSB[] PROGMEM = "Disable USB";
    static const char enableUSB[] PROGMEM = "Enable USB";
    static const char disableLora[] PROGMEM = "Disable LoRa";
    static const char enableLora[] PROGMEM = "Enable Lora";
    static const char log[] PROGMEM = "Log";
    static const char compiledOn[] PROGMEM = "Compiled On";
    static const char leftJoy[] PROGMEM = "Left Joy";
    static const char rightJoy[] PROGMEM = "Right Joy";
    static const char xAxis[] PROGMEM = "X-Axis";
    static const char yAxis[] PROGMEM = "Y-Axis";
    static const char fmode[] PROGMEM = "F-Mode";
    static const char armed[] PROGMEM = "Armed";
    static const char next[] PROGMEM = "Next";
    static const char previous[] PROGMEM = "Previous";
    static const char empty[] PROGMEM = "";
    static const char land[] PROGMEM = "Land";
    static const char manual[] PROGMEM = "Manual";
    static const char hold[] PROGMEM = "Hold";
    static const char waypoint[] PROGMEM = "Waypoint";
    static const char launch[] PROGMEM = "Launch";
    static const char compileTime[] PROGMEM = __TIME__;
    static const char compileDate[] PROGMEM = __DATE__;
    static const char version[] PROGMEM = "0.1-AVR";
}

char* getData(const char* addr) {
    static uint8_t data[12] = {' '};
    uint8_t c = 0;
    while ((data[c] = pgm_read_byte(addr + c++)));
    for(;c< sizeof(data);c++) {
        data[c] = ' ';
    }
    return (char*)data;
}

#endif //RADIOCONTROLSOFTWARE_STRINGS_H
