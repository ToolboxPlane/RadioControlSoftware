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
#include "materialcolors.h"
#include "colors.h"

label_t lbl_left_joystick, lbl_right_joystick, label_flightmode, label_error;

void ui_draw_label(const char *text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
    ili9341_setcursor(x,y);
    ili9341_settextcolour(color);
    ili9341_settextsize(size);

    for(uint8_t c=0; c<len; c++) {
        ili9341_write((uint8_t)(text[c]));
    }
}


void ui_init() {
    ili9341_setRotation(2);//rotate screen
    ili9341_clear(BACKGROUND_COLOR);//fill screen with black colour
    ili9341_fillrect(0,0,240, 10, NOTIF_COLOR);

    label_init(&lbl_right_joystick, NOTIF_COLOR, &ui_draw_label);
    label_init(&label_flightmode, NOTIF_COLOR, &ui_draw_label);

    label_init(&lbl_left_joystick, NOTIF_COLOR, &ui_draw_label);
    label_set_position(&lbl_left_joystick, 4, 1);
    label_set_color(&lbl_left_joystick, NOTIF_TEXT_COLOR);
    label_set_size(&lbl_left_joystick, 1);

    label_init(&lbl_right_joystick, NOTIF_COLOR, &ui_draw_label);
    label_set_position(&lbl_right_joystick, 170, 1);
    label_set_color(&lbl_right_joystick, NOTIF_TEXT_COLOR);
    label_set_size(&lbl_right_joystick, 1);

    label_init(&label_flightmode, NOTIF_COLOR, &ui_draw_label);
    label_set_position(&label_flightmode, 90, 1);
    label_set_color(&label_flightmode, NOTIF_TEXT_COLOR);
    label_set_size(&label_flightmode, 1);

    label_init(&label_error, BACKGROUND_COLOR, &ui_draw_label);
    label_set_position(&label_error, 10, 135);
    label_set_color(&label_error, ERROR_COLOR);
    label_set_size(&label_error, 3);
}

void ui_update(uint8_t isArmed, const char* flightmode) {
    label_set_color(&lbl_left_joystick, isArmed ? r8g8b8_to_r5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    label_set_color(&lbl_right_joystick, isArmed ? r8g8b8_to_r5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    label_set_color(&label_flightmode, isArmed ? r8g8b8_to_r5g6b5(RED_P500) : NOTIF_TEXT_COLOR);

    char buf[11] = {' '};
    buf[0] = '(';
    itoa(joystick_get_x_value(&joystick_left), buf+1, 10);
    buf[5] = '|';
    itoa(joystick_get_y_value(&joystick_left), buf+6, 10);
    buf[10] = ')';
    label_set_text(&lbl_left_joystick, buf, 11);

    for(uint8_t c=0; c<4; c++) {
        buf[1+c] = buf[6+c] = ' ';
    }
    itoa(joystick_get_x_value(&joystick_right), buf+1, 10);
    itoa(joystick_get_y_value(&joystick_right), buf+6, 10);
    label_set_text(&lbl_right_joystick, buf, 11);

    label_set_text(&label_flightmode, TR(flightmode));
}

void ui_show_error(const char *error) {
    label_set_text(&label_error, TR(error));
    while (1);
}
