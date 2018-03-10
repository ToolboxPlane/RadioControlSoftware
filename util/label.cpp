#include "label.hpp"

Label::Label() {
    this->background = 0;
    this->len = 0;
}


Label::Label(uint16_t background) {
    this->background = background;
}

void Label::setPosition(uint16_t x, uint16_t y) {
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);
    drawLabel(this->text, this->len, x, y, this->size, this->color);

    this->x = x;
    this->y = y;
}

void Label::clear() {
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);

    this->len = 0;
}

void Label::setColor(uint16_t color) {
    drawLabel(this->text, this->len, this->x, this->y, this->size, color);

    this->color = color;
}

void Label::setText(const char* text, uint8_t len) {
    uint8_t maxLen = len > this->len ? len : this->len;
    char write[len];

    for (uint8_t c = 0; c < maxLen; c++) {
        if(c < len && c < this->len) {
            if (text[c] == this->text[c]) {
                write[c] = ' ';
                this->text[c] = ' ';
            } else {
                write[c] = text[c];
            }
        } else if (c < len) {
            write[c] = text[c];
        }
    }

    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);
    drawLabel(write, len, this->x, this->y, this->size, this->color);

    uint8_t realLen = 0;
    for(uint8_t c=0; c<len; c++) {
        if(text[c] != ' ') {
            realLen = c+1;
        }
        this->text[c] = text[c];
    }
    this->len = realLen;
}


void Label::setNumber(int16_t num) {
    char buffer[6];
    char sign = num >= 0 ? '+' : '-';
    if(num < 0) {
        num *= -1;
    }
    if(num == 0) {
        buffer[0] = '0';
        this->setText(buffer, 1);
        return;
    }

    for(uint8_t c=0; c<5; c++) {
        if(num != 0) {
            buffer[5 - c] = (char) ((num % 10) + '0');
            num /= 10;
        } else {
            if(sign == '-') {
                buffer[5 - c] = sign;
                this->setText(buffer + (5 - c), c + 1);
            } else {
                this->setText(buffer + (5-c) +1, c);
            }
            break;
        }
    }

}

void Label::forceText(char* text, uint8_t len) {
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);
    drawLabel(text, len, this->x, this->y, this->size, this->color);

    for(uint8_t c=0; c<len; c++) {
        this->text[c] = text[c];
    }
    this->len = len;
}

void Label::setSize(uint8_t size) {
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);
    drawLabel(this->text, this->len, this->x, this->y, size, this->color);

    this->size = size;
}

void Label::update() {
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->background);
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->color);
}

void Label::append(const char *text, uint8_t addLen) {
    char newText[12];
    for(uint8_t c=0; c<addLen+len; c++) {
        if(c < len) {
            newText[c] = this->text[c];
        } else {
            newText[c] = text[c-len];
        }
    }
    this->setText(newText, addLen+len);
/*    this->len += addLen;
    drawLabel(this->text, this->len, this->x, this->y, this->size, this->color);*/
}

void Label::append(int number) {
    uint8_t buf[4];
    for(uint8_t c=0; c<4; c++) {
        buf[3-c] = (uint8_t)((number % 10) + '0');
        number /= 10;
        if(number == 0) {
            this->append((char*)(buf+3-c), c+1);
            break;
        }
    }
}
