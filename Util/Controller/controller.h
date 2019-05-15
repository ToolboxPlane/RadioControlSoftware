#ifndef RADIOCONTROLSOFTWARE_CONTROLLER_H
#define RADIOCONTROLSOFTWARE_CONTROLLER_H


#include <stdint.h>
#include "joystick.h"
#include "screen.h"

extern joystick_t joystick_left, joystick_right;

extern controller_screen_t page;

void controller_init(void);
void controller_set_debug(uint8_t index, uint16_t val);
int8_t controller_get_selection(void);
void controller_update_buttons(void);
void controller_handle_events(int8_t sel);

#endif
