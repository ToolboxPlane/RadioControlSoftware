#ifndef _MODEL_H
#define _MODEL_H

#include <avr/eeprom.h>
#include <stdbool.h>

typedef enum {
    ANGLE = 0,
    LAUNCH = 1,
    LAND = 2,
    HOLD = 3,
    WAYPOINT = 4
} Flightmode;

extern Flightmode flightmode;
extern uint8_t armed;
extern uint16_t debugVals[6];
extern int16_t rssi;
extern int16_t snr;
extern uint16_t received, sent;
extern int16_t remoteRssi, remoteSnr;

bool loraEnabled(void);
bool serialEnabled(void);
void setLoraEnabled(bool enabled);
void setSerialEnabled(bool enabled);
char* getFlightMode(Flightmode mode);

#endif
