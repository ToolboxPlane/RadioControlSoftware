//
// Created by paul on 25.07.16.
//

#ifndef SMARTWATCH2_LABEL_HPP
#define SMARTWATCH2_LABEL_HPP

#include <stdint.h>

extern void drawLabel(const char* text,uint8_t len, uint16_t x, uint16_t y, uint8_t size, uint16_t color);

class Label {
public:
    Label();

    explicit Label(uint16_t background);

    void setPosition(uint16_t x, uint16_t y);

    void setText(const char* text, uint8_t len);

    void append(const char* text, uint8_t addLen);

    void append(int number);

    void setNumber(int16_t num);

    void clear();

    void setColor(uint16_t color);

    void setSize(uint8_t size);

    void update();

private:
    void forceText(char* text, uint8_t len);

    char text[12];
    uint8_t len;
    uint16_t x, y;
    uint16_t color;
    uint8_t size;
    uint16_t background;
};

#endif //SMARTWATCH2_LABEL_HPP
