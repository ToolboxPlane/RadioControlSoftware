#ifndef _UI_H
#define _UI_H

#include "label.hpp"
#include "materialColors.h"
#include "colorConvert.h"
#include "Joystick.hpp"

#define BACKGROUND_COLOR r8g8b8Tor5g6b5(Grey::P300)
#define NOTIF_COLOR r8g8b8Tor5g6b5(Black)
#define BUTTON_COLOR r8g8b8Tor5g6b5(DeepOrange::P500)
#define NOTIF_TEXT_COLOR r8g8b8Tor5g6b5(White)
#define BUTTON_TEXT_COLOR r8g8b8Tor5g6b5(White)
#define BUTTON_TEXT_SELECTED_COLOR r8g8b8Tor5g6b5(Grey::P500)

extern Joystick joyLeft, joyRight;

namespace ui {
    //Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

    Label lblLeftJoy(NOTIF_COLOR),
            lblRightJoy(NOTIF_COLOR),
            lblLeftPress(NOTIF_COLOR),
            lblRightPress(NOTIF_COLOR);

    Label lblFlightMode(NOTIF_COLOR);
    Label buttonLabel[6];

    void load() {
        /*tft.begin();
        tft.fillScreen(BACKGROUND_COLOR);
        tft.setRotation(2);

        tft.fillRect(0, 0, 240, 10, NOTIF_COLOR);

        tft.fillRoundRect(10, 20, 220, 40, 8, BUTTON_COLOR);
        tft.fillRoundRect(10, 70, 220, 40, 8, BUTTON_COLOR);
        tft.fillRoundRect(10, 120, 220, 40, 8, BUTTON_COLOR);
        tft.fillRoundRect(10, 170, 220, 40, 8, BUTTON_COLOR);
        tft.fillRoundRect(10, 220, 220, 40, 8, BUTTON_COLOR);
        tft.fillRoundRect(10, 270, 220, 40, 8, BUTTON_COLOR);*/

        ili9341_init();//initial driver setup to drive ili9341
        ili9341_clear(BACKGROUND_COLOR);//fill screen with black colour
        ili9341_setRotation(2);//rotate screen

        ili9341_fillrect(0,0,240, 10, NOTIF_COLOR);

        ili9341_fillrect(10,20,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,70,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,120,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,170,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,220,220,40, BUTTON_COLOR);
        ili9341_fillrect(10,270,220,40, BUTTON_COLOR);

        lblLeftJoy.setPosition(20, 1);
        lblLeftJoy.setColor(NOTIF_TEXT_COLOR);
        lblLeftJoy.setSize(1);

        lblRightJoy.setPosition(152, 1);
        lblRightJoy.setColor(NOTIF_TEXT_COLOR);
        lblRightJoy.setSize(1);

        lblLeftPress.setPosition(0, 1);
        lblLeftPress.setColor(NOTIF_TEXT_COLOR);
        lblLeftPress.setSize(1);

        lblRightPress.setPosition(220, 1);
        lblRightPress.setColor(NOTIF_TEXT_COLOR);
        lblRightPress.setSize(1);

        lblFlightMode.setPosition(90, 1);
        lblFlightMode.setColor(NOTIF_TEXT_COLOR);
        lblFlightMode.setSize(1);

        for (uint8_t c = 0; c <= 5; c++) {
            buttonLabel[c] = Label(BUTTON_COLOR);
            buttonLabel[c].setPosition(16, 30 + c * 50);
            buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
            buttonLabel[c].setSize(3);
        }
    }

    void update(uint8_t isArmed/*, String flightmode*/) {
        lblLeftJoy.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblRightJoy.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblLeftPress.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblRightPress.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);
        lblFlightMode.setColor(isArmed ? r8g8b8Tor5g6b5(Red::P500) : NOTIF_TEXT_COLOR);

       /* lblLeftJoy.setText(
                "(" + String(joyLeft.getXValue()) + "|" + String(joyLeft.getYValue()) + ")"
        );
        lblRightJoy.setText(
                "(" + String(joyRight.getXValue()) + "|" + String(joyRight.getYValue()) + ")"
        );
        lblLeftPress.setText(joyLeft.getButton() ? "ON " : "OFF", 3);
        lblRightPress.setText(joyRight.getButton() ? " ON" : "OFF", 3);
        lblFlightMode.setText(flightmode);*/
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
