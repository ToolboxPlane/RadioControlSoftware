#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

#include <stdint.h>
#include "joystick.h"

joystick_t joyLeft, joyRight;

typedef enum {
    START,
    CALIBRATE,
    FLIGHTMODES,
    SETTINGS,
    DEBUG,
    LOG,
    DOWNLINK,
    RECEIVED_DATA
} Page;

extern Page page;

void load(void);
void setDebug(uint8_t index, uint16_t val);
int8_t getSelection(void);
void updateButtons(void);
void handleEvent(int8_t sel);

#endif
