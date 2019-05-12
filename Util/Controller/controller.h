#ifndef RADIOCONTROLSOFTWARE_CONTROLLER_H
#define RADIOCONTROLSOFTWARE_CONTROLLER_H

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

#include <stdint.h>
#include "joystick.h"

extern joystick_t joystick_left, joystick_right;

typedef enum {
    START,
    CALIBRATE,
    FLIGHTMODES,
    SETTINGS,
    DEBUG,
    LOG,
    DOWNLINK,
    RECEIVED_DATA
} controller_page_t;

extern controller_page_t page;

void controller_init(void);
void controller_set_debug(uint8_t index, uint16_t val);
int8_t controller_get_selection(void);
void controller_update_buttons(void);
void controller_handle_events(int8_t sel);

#endif
