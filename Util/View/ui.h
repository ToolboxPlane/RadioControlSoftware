#ifndef _UI_H
#define _UI_H

#include <stdlib.h>
#include <string.h>
#include "label.h"
#include "materialColors.h"
#include "colorconvert.h"
#include "../Controller/Joystick.hpp"
#include "strings.h"

#define BACKGROUND_COLOR r8g8b8Tor5g6b5(GREY_P300)
#define NOTIF_COLOR r8g8b8Tor5g6b5(BLACK)
#define BUTTON_COLOR r8g8b8Tor5g6b5(DEEP_ORANGE_P500)
#define NOTIF_TEXT_COLOR r8g8b8Tor5g6b5(WHITE)
#define BUTTON_TEXT_COLOR r8g8b8Tor5g6b5(WHITE)
#define BUTTON_TEXT_SELECTED_COLOR r8g8b8Tor5g6b5(GREY_P500)


    void ui_load(void);

    void ui_update(uint8_t isArmed, char* flightmode);

void ui_draw_label(const char* text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color);

#endif
