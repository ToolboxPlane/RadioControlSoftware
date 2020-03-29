#ifndef RADIOCONTROLSOFTWARE_UI_H
#define RADIOCONTROLSOFTWARE_UI_H

#include <stdint.h>

void ui_init(void);
void ui_update(uint8_t isArmed, const char* flightmode);
void ui_draw_label(const char *text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color);
void ui_show_error(const char *error);
#endif
