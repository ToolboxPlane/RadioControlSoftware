#ifndef _MODEL_H
#define _MODEL_H

#include "Joystick.hpp"

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
    String debugVals[6];
    int8_t rssi;
    uint8_t flightmodeChannel = 0;
    uint8_t armedChannnel = 0;

    String getFlightMode(Flightmode mode = flightmode) {
        switch (mode) {
            case MANUAL:
                return F("Manual");
            case LAUNCH:
                return F("Launch");
            case LAND:
                return F("Land");
            case HOLD:
                return F("Hold");
            case WAYPOINT:
                return F("Waypoint");
            default:
                return "";
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
        EEPROM.write(EEPROM_CHANNEL_START_REG+type, channel);
    }

     void loadChannelData() {
        for(uint8_t c=0; c<11; c++) {
            mapToChannel(c, EEPROM.read(c+EEPROM_CHANNEL_START_REG));
        }
    }

    bool loraEnabled() {
        return EEPROM.read(EEPROM_CONFIG_REG) & (0b1 << LORA_ENABLE_BIT);
    }


    bool serialEnabled() {
        return EEPROM.read(EEPROM_CONFIG_REG) & (0b1 << SERIAL_ENABLE_BIT);
    }

    void setLoraEnabled(bool enabled) {
        uint8_t configByte = EEPROM.read(EEPROM_CONFIG_REG);
        if(enabled) {
            configByte |= (0b1 << LORA_ENABLE_BIT);
        } else {
            configByte &= ~(0b1 << LORA_ENABLE_BIT);
        }
        EEPROM.write(EEPROM_CONFIG_REG, configByte);
    }

    void setSerialEnabled(bool enabled) {
        uint8_t configByte = EEPROM.read(EEPROM_CONFIG_REG);
        if(enabled) {
            configByte |= (0b1 << SERIAL_ENABLE_BIT);
        } else {
            configByte &= ~(0b1 << SERIAL_ENABLE_BIT);
        }
        EEPROM.write(EEPROM_CONFIG_REG, configByte);
    }
}

#endif
