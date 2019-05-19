/**
 * @file ui.c
 * @author paul
 * @date 12.05.19
 * @brief ui @TODO
 */
#include <stdlib.h>
#include "ui.h"

#include "Elements/label.h"
#include "../../Drivers/ili9341.h"
#include "../../Drivers/ili9341gfx.h"
#include "../Controller/controller.h"
#include "strings.h"
#include "colorconvert.h"
#include "materialColors.h"
#include "colors.h"

label_t lblLeftJoy, lblRightJoy, lblFlightMode;
label_t ui_buttonLabel[6];

void ui_drawLabel(const char* text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
    ili9341_setcursor(x,y);
    ili9341_settextcolour(color);
    ili9341_settextsize(size);

    for(uint8_t c=0; c<len; c++) {
        ili9341_write((uint8_t)(text[c]));
    }
}


void ui_init() {
    ili9341_init();//initial driver setup to drive ili9341
    ili9341_setRotation(2);//rotate screen
    ili9341_clear(BACKGROUND_COLOR);//fill screen with black colour
    ili9341_fillrect(0,0,240, 10, NOTIF_COLOR);

    label_init(&lblRightJoy, NOTIF_COLOR, &ui_drawLabel);
    label_init(&lblFlightMode, NOTIF_COLOR, &ui_drawLabel);

    label_init(&lblLeftJoy, NOTIF_COLOR, &ui_drawLabel);
    label_set_position(&lblLeftJoy, 4, 1);
    label_set_color(&lblLeftJoy, NOTIF_TEXT_COLOR);
    label_set_size(&lblLeftJoy, 1);

    label_init(&lblRightJoy, NOTIF_COLOR, &ui_drawLabel);
    label_set_position(&lblRightJoy, 170, 1);
    label_set_color(&lblRightJoy, NOTIF_TEXT_COLOR);
    label_set_size(&lblRightJoy, 1);

    label_init(&lblFlightMode, NOTIF_COLOR, &ui_drawLabel);
    label_set_position(&lblFlightMode, 90, 1);
    label_set_color(&lblFlightMode, NOTIF_TEXT_COLOR);
    label_set_size(&lblFlightMode, 1);
}

void ui_update(uint8_t isArmed, const char* flightmode) {
    label_set_color(&lblLeftJoy, isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    label_set_color(&lblRightJoy, isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    label_set_color(&lblFlightMode, isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);

    char buf[11] = {' '};
    buf[0] = '(';
    itoa(joystick_get_x_value(&joystick_left), buf+1, 10);
    buf[5] = '|';
    itoa(joystick_get_y_value(&joystick_right), buf+6, 10);
    buf[10] = ')';
    label_set_text(&lblLeftJoy, buf, 11);

    for(uint8_t c=0; c<4; c++) {
        buf[1+c] = buf[6+c] = ' ';
    }
    itoa(joystick_get_x_value(&joystick_left), buf+1, 10);
    itoa(joystick_get_y_value(&joystick_right), buf+6, 10);
    label_set_text(&lblRightJoy, buf, 11);

    label_set_text(&lblFlightMode, TR(flightmode));
}
