#ifndef _MODEL_H
#define _MODEL_H

#include "../Controller/Joystick.hpp"
#include "../View/strings.h"

#define EEPROM_CONFIG_REG 32
#define EEPROM_CHANNEL_START_REG 64
#define SERIAL_ENABLE_BIT 0
#define LORA_ENABLE_BIT 1

extern Joystick joyLeft, joyRight;

namespace model {
    enum Flightmode {
        ANGLE = 0,
        LAUNCH = 1,
        LAND = 2,
        HOLD = 3,
        WAYPOINT = 4
    };

    Flightmode flightmode = LAUNCH;
    uint8_t armed = false;
    uint16_t debugVals[6];
    int16_t rssi;
    int16_t snr;
    uint16_t received, sent;
    int16_t remoteRssi, remoteSnr;

    char* getFlightMode(Flightmode mode = flightmode) {
        switch (mode) {
            case ANGLE:
                return (char*)string_angle;
            case LAUNCH:
                return (char*)string_launch;
            case LAND:
                return (char*)string_land;
            case HOLD:
                return (char*)string_hold;
            case WAYPOINT:
                return (char*)string_waypoint;
            default:
                return (char*)string_empty;
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
