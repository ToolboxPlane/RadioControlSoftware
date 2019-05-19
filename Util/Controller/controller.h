#ifndef RADIOCONTROLSOFTWARE_CONTROLLER_H
#define RADIOCONTROLSOFTWARE_CONTROLLER_H


#include <stdint.h>
#include "joystick.h"
#include "screen.h"

extern joystick_t joystick_left, joystick_right;

void controller_init(void);
void controller_update(void);

#endif
