#ifndef RADIOCONTROLSOFTWARE_UI_H
#define RADIOCONTROLSOFTWARE_UI_H

#include <stdint.h>
#include <stdbool.h>
#include "Elements/label.h"

extern label_t lblLeftJoy, lblRightJoy, lblFlightMode;
extern label_t ui_buttonLabel[6];

void ui_init(void);
void ui_update(uint8_t isArmed, const char* flightmode);
void ui_button_highlight(uint8_t button_id, bool highlighted);

void ui_drawLabel(const char* text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color);
#endif
