/**
 * @file model.cpp
 * @author paul
 * @date 12.05.19
 * @brief model @TODO
 */

#include "model.h"
#include "../View/strings.h"

#define EEPROM_CONFIG_REG 32
#define EEPROM_CHANNEL_START_REG 64
#define SERIAL_ENABLE_BIT 0
#define LORA_ENABLE_BIT 1

flightmode_t flightmode = LAUNCH;
uint8_t armed = false;
uint16_t debug_vals[6];
int16_t rssi;
int16_t snr;
uint16_t received, sent;
int16_t remote_rssi, remote_snr;

bool model_get_lora_enabled(void) {
    return (eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG) >> LORA_ENABLE_BIT) & 1;
}


bool model_get_serial_enabled(void) {
    return (eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG) >> SERIAL_ENABLE_BIT) & 1;
}

void model_set_lora_enabled(bool enabled) {
    uint8_t configByte = eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG);
    if(enabled) {
        configByte |= (0b1 << LORA_ENABLE_BIT);
    } else {
        configByte &= ~(0b1 << LORA_ENABLE_BIT);
    }
    eeprom_update_byte((uint8_t*)EEPROM_CONFIG_REG, configByte);
}

void model_set_serial_enabled(bool enabled) {
    uint8_t configByte = eeprom_read_byte((uint8_t*)EEPROM_CONFIG_REG);
    if(enabled) {
        configByte |= (0b1 << SERIAL_ENABLE_BIT);
    } else {
        configByte &= ~(0b1 << SERIAL_ENABLE_BIT);
    }
    eeprom_update_byte((uint8_t*)EEPROM_CONFIG_REG, configByte);
}

char* model_get_flightmode_string(flightmode_t mode) {
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

 