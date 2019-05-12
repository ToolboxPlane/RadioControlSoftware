#ifndef RADIOCONTROLSOFTWARE_MODEL_H
#define RADIOCONTROLSOFTWARE_MODEL_H

#include <avr/eeprom.h>
#include <stdbool.h>

typedef enum {
    ANGLE = 0,
    LAUNCH = 1,
    LAND = 2,
    HOLD = 3,
    WAYPOINT = 4
} flightmode_t;

extern flightmode_t flightmode;
extern uint8_t armed;
extern uint16_t debug_vals[6];
extern int16_t rssi;
extern int16_t snr;
extern uint16_t received, sent;
extern int16_t remote_rssi, remote_snr;

bool model_get_lora_enabled(void);
bool model_get_serial_enabled(void);
void model_set_lora_enabled(bool enabled);
void model_set_serial_enabled(bool enabled);
char* model_get_flightmode_string(flightmode_t mode);

#endif
