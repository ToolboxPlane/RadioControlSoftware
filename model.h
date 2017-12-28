#ifndef _MODEL_H
#define _MODEL_H

#define EEPROM_CONFIG_REG 8
#define SERIAL_ENABLE_BIT 0
#define LORA_ENABLE_BIT 1

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