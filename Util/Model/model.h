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
} model_flightmode_t;

extern model_flightmode_t model_flightmode;
extern uint8_t model_armed;
extern int16_t model_rssi;
extern int16_t model_snr;
extern uint16_t model_received, model_sent;
extern int16_t model_remote_rssi, model_remote_snr;
extern uint16_t model_receive_data[8];

void model_init(void);
bool model_get_lora_enabled(void);
bool model_get_serial_enabled(void);
void model_set_lora_enabled(bool enabled);
void model_set_serial_enabled(bool enabled);
char* model_get_flightmode_string(model_flightmode_t mode);

#endif
