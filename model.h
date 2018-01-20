#ifndef _MODEL_H
#define _MODEL_H

#include "Joystick.hpp"
#include "strings.h"

#define EEPROM_CONFIG_REG 32
#define EEPROM_CHANNEL_START_REG 64
#define SERIAL_ENABLE_BIT 0
#define LORA_ENABLE_BIT 1

extern Joystick joyLeft, joyRight;

namespace model {
    enum Flightmode {
        MANUAL = 0,
        LAUNCH = 1,
        LAND = 2,
        HOLD = 3,
        WAYPOINT = 4
    };

    Flightmode flightmode = LAUNCH;
    uint8_t armed = false;
    uint16_t debugVals[6];
    int8_t rssi;
    uint8_t flightmodeChannel = 0;
    uint8_t armedChannnel = 0;

    char* getFlightMode(Flightmode mode = flightmode) {
        switch (mode) {
            case MANUAL:
                return (char*)strings::manual;
            case LAUNCH:
                return (char*)strings::launch;
            case LAND:
                return (char*)strings::land;
            case HOLD:
                return (char*)strings::hold;
            case WAYPOINT:
                return (char*)strings::waypoint;
            default:
                return (char*)strings::empty;
        }
    }

    void mapToChannel(uint8_t type, uint8_t channel) {
        switch(type) {
            case 0:
                joyLeft.setXChannel(channel);
                break;
            case 1:
                joyLeft.setYChannel(channel);
                break;
            case 2:
                joyLeft.setBtnChannel(channel);
                break;
            case 5:
                joyRight.setXChannel(channel);
                break;
            case 6:
                joyRight.setYChannel(channel);
                break;
            case 7:
                joyRight.setBtnChannel(channel);
                break;
            case 10:
                flightmodeChannel = channel;
                break;
            case 11:
                armedChannnel = channel;
                break;
        }

        eeprom_update_byte((uint8_t*)(EEPROM_CHANNEL_START_REG+type), channel);
    }

     void loadChannelData() {
        for(uint8_t c=0; c<11; c++) {
            mapToChannel(c, eeprom_read_byte((uint8_t*)(c+EEPROM_CHANNEL_START_REG)));
        }
    }

    bool loraEnabled() {
        return eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG) & (0b1 << LORA_ENABLE_BIT);
    }


    bool serialEnabled() {
        return eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG) & (0b1 << SERIAL_ENABLE_BIT);
    }

    void setLoraEnabled(bool enabled) {
        uint8_t configByte = eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG);
        if(enabled) {
            configByte |= (0b1 << LORA_ENABLE_BIT);
        } else {
            configByte &= ~(0b1 << LORA_ENABLE_BIT);
        }
        eeprom_update_byte((uint8_t*)EEPROM_CONFIG_REG, configByte);
    }

    void setSerialEnabled(bool enabled) {
        uint8_t configByte = eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG);
        if(enabled) {
            configByte |= (0b1 << SERIAL_ENABLE_BIT);
        } else {
            configByte &= ~(0b1 << SERIAL_ENABLE_BIT);
        }
        eeprom_update_byte((uint8_t*)EEPROM_CONFIG_REG, configByte);
    }
}

#endif
