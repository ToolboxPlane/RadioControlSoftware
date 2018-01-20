#ifndef _UI_H
#define _UI_H

#include "label.hpp"
#include "materialColors.h"
#include "colorConvert.h"
#include "Joystick.hpp"
#include "strings.h"

#define BACKGROUND_COLOR r8g8b8Tor5g6b5(Grey::P300)
#define NOTIF_COLOR r8g8b8Tor5g6b5(Black)
#define BUTTON_COLOR r8g8b8Tor5g6b5(DeepOrange::P500)
#define NOTIF_TEXT_COLOR r8g8b8Tor5g6b5(White)
#define BUTTON_TEXT_COLOR r8g8b8Tor5g6b5(White)
#define BUTTON_TEXT_SELECTED_COLOR r8g8b8Tor5g6b5(Grey::P500)

extern Joystick joyLeft, joyRight;

namespace ui {
    Label lblLeftJoy(NOTIF_COLOR),
            lblRightJoy(NOTIF_COLOR);

    Label lblFlightMode(NOTIF_COLOR);
    Label buttonLabel[6] = {Label(BUTTON_COLOR),
                            Label(BUTTON_COLOR),
                            Label(BUTTON_COLOR),
                            Label(BUTTON_COLOR),
                            Label(BUTTON_COLOR),
                            Label(BUTTON_COLOR)};

    void load() {
        ili9341_init();//initial driver setup to drive ili9341
        ili9341_setRotation(2);//rotate screen
        ili9341_clear(BACKGROUND_COLOR);//fill screen with black colour
        ili9341_fillrect(0,0,240, 10, NOTIF_COLOR);

        ili9341_fillrect(10,20,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,70,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,120,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,170,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,220,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,270,220,40, BUTTON_COLOR);

        lblLeftJoy.setPosition(4, 1);
        lblLeftJoy.setColor(NOTIF_TEXT_COLOR);
        lblLeftJoy.setSize(1);

        lblRightJoy.setPosition(200, 1);
        lblRightJoy.setColor(NOTIF_TEXT_COLOR);
        lblRightJoy.setSize(1);

        lblFlightMode.setPosition(90, 1);
        lblFlightMode.setColor(NOTIF_TEXT_COLOR);
        lblFlightMode.setSize(1);
        for (uint16_t c = 0; c < 6; c++) {
            buttonLabel[c].setPosition(16,30 + c * 50);
            buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
            buttonLabel[c].setSize(3);
        }
    }

    void update(uint8_t isArmed, char* flightmode) {
        lblLeftJoy.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblRightJoy.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblFlightMode.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);

        lblLeftJoy.setNumber(joyLeft.getXValue());
        lblRightJoy.setNumber(joyRight.getXValue());
       /* lblLeftJoy.setText(
                "(" + String(joyLeft.getXValue()) + "|" + String(joyLeft.getYValue()) + ")"
        );
        lblRightJoy.setText(
                "(" + String(joyRight.getXValue()) + "|" + String(joyRight.getYValue()) + ")"
        );*/
        lblFlightMode.setText(F(flightmode));
    }
}

void drawLabel(char* text, uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color) {
    ili9341_setcursor(x,y);
    ili9341_settextcolour(color);
    ili9341_settextsize(size);

    for(uint8_t c=0; c<len; c++) {
        ili9341_write((uint8_t)(text[c]));
    }
}

#endif
