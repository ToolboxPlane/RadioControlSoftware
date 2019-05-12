#ifndef RADIOCONTROLSOFTWARE_UI_H
#define RADIOCONTROLSOFTWARE_UI_H

#include <stdint.h>
#include <stdbool.h>
#include "label.h"

extern label_t lblLeftJoy, lblRightJoy, lblFlightMode;
extern label_t ui_buttonLabel[6];

void ui_init(void);
void ui_update(uint8_t isArmed, const char* flightmode);
void ui_button_highlight(uint8_t button_id, bool highlighted);

#endif
