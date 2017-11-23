//
// Created by paul on 25.07.16.
//

#ifndef SMARTWATCH2_LABEL_HPP
#define SMARTWATCH2_LABEL_HPP

#include <Arduino.h>
#include <stdint.h>

extern void drawLabel(String text, uint16_t x, uint16_t y, uint8_t size, uint16_t color);

class Label {
public:
    Label();

    Label(uint16_t background);

    void setPosition(uint16_t x, uint16_t y);

    void setText(String text);

    void setNumber(uint8_t num);

    void setNumber(uint8_t num, String unit);

    void append(String text);

    void clear();

    void setColor(uint16_t color);

    void setSize(uint8_t size);

    void update();

private:
    void forceText(String text);

    String text;
    uint16_t x, y;
    uint16_t color;
    uint8_t size;
    uint16_t background;
};

#endif //SMARTWATCH2_LABEL_HPP
