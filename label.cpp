#include "label.hpp"

Label::Label() {
    this->background = 0;
}


Label::Label(uint16_t background) {
    this->background = background;
}

void Label::setPosition(uint16_t x, uint16_t y) {
    drawLabel(this->text, this->x, this->y, this->size, this->background);
    drawLabel(this->text, x, y, this->size, this->color);

    this->x = x;
    this->y = y;
}

void Label::clear() {
    drawLabel(this->text, this->x, this->y, this->size, this->background);

    this->text = "";
}

void Label::setColor(uint16_t color) {
    drawLabel(this->text, this->x, this->y, this->size, color);

    this->color = color;
}

void Label::setText(String text) {
    if (text != this->text) {
        uint8_t len = text.length() > this->text.length() ?
                      text.length() : this->text.length();
        String write = text;
        String del = this->text;
        for (uint8_t c = 0; c < len; c++) {
            if (text.charAt(c) == this->text.charAt(c)) {
                write.setCharAt(c, ' ');
                del.setCharAt(c, ' ');
            }
        }

        drawLabel(del, this->x, this->y, this->size, this->background);
        drawLabel(write, this->x, this->y, this->size, this->color);

        this->text = text;
    }
}

void Label::append(String text) {
    this->setText(this->text + text);
}

void Label::setNumber(uint8_t num) {
    char buffer[4];

    itoa(num, buffer, 10);

    this->setText(String(buffer));
}

void Label::setNumber(uint8_t num, String unit) {
    char buffer[4];

    itoa(num, buffer, 10);

    this->setText(String(buffer) + unit);
}

void Label::forceText(String text) {
    drawLabel(this->text, this->x, this->y, this->size, this->background);
    drawLabel(text, this->x, this->y, this->size, this->color);

    this->text = text;
}

void Label::setSize(uint8_t size) {
    drawLabel(this->text, this->x, this->y, this->size, this->background);
    drawLabel(this->text, this->x, this->y, size, this->color);

    this->size = size;
}

void Label::update() {
    drawLabel(this->text, this->x, this->y, this->size, this->background);
    drawLabel(this->text, this->x, this->y, this->size, this->color);
}