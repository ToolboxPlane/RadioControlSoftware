/**
 * @file ui.c
 * @author paul
 * @date 12.05.19
 * @brief ui @TODO
 */
#include "ui.h"
#include "label.h"
#include "../../Drivers/ili9341.h"

Label lblLeftJoy(NOTIF_COLOR),
        lblRightJoy(NOTIF_COLOR);

Label lblFlightMode(NOTIF_COLOR);
Label buttonLabel[6] = {Label(BUTTON_COLOR),
                        Label(BUTTON_COLOR),
                        Label(BUTTON_COLOR),
                        Label(BUTTON_COLOR),
                        Label(BUTTON_COLOR),
                        Label(BUTTON_COLOR)};

void ui_load() {
    ili9341_init();//initial driver setup to drive ili9341
    ili9341_setRotation(2);//rotate screen
    ili9341_clear(BACKGROUND_COLOR);//fill screen with black colour
    ili9341_fillrect(0,0,240, 10, NOTIF_COLOR);

    lblLeftJoy.setPosition(4, 1);
    lblLeftJoy.setColor(NOTIF_TEXT_COLOR);
    lblLeftJoy.setSize(1);

    lblRightJoy.setPosition(170, 1);
    lblRightJoy.setColor(NOTIF_TEXT_COLOR);
    lblRightJoy.setSize(1);

    lblFlightMode.setPosition(90, 1);
    lblFlightMode.setColor(NOTIF_TEXT_COLOR);
    lblFlightMode.setSize(1);
    for (uint16_t c = 0; c < 6; c++) {
        ili9341_fillrect(6,20 + 50*c,228,40, BUTTON_COLOR);
        buttonLabel[c].setPosition(14,30 + c * 50);
        buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
        buttonLabel[c].setSize(3);
    }
}

void ui_update(uint8_t isArmed, char* flightmode) {
    lblLeftJoy.setColor(isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    lblRightJoy.setColor(isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);
    lblFlightMode.setColor(isArmed ? r8g8b8Tor5g6b5(RED_P500) : NOTIF_TEXT_COLOR);

    char buf[11] = {' '};
    buf[0] = '(';
    itoa(joyLeft.getXValue(), buf+1, 10);
    buf[5] = '|';
    itoa(joyLeft.getYValue(), buf+6, 10);
    buf[10] = ')';
    lblLeftJoy.setText(buf, 11);

    for(uint8_t c=0; c<4; c++) {
        buf[1+c] = buf[6+c] = ' ';
    }
    itoa(joyRight.getXValue(), buf+1, 10);
    itoa(joyRight.getYValue(), buf+6, 10);
    lblRightJoy.setText(buf,11);

    lblFlightMode.setText(TR(flightmode));
}
}

void ui_drawLabel(const char* text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
    ili9341_setcursor(x,y);
    ili9341_settextcolour(color);
    ili9341_settextsize(size);

    for(uint8_t c=0; c<len; c++) {
        ili9341_write((uint8_t)(text[c]));
    }
}

