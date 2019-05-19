#include "label.h"

void label_init(label_t *label, uint16_t background, draw_f_t draw_f) {
    label->background = background;
    label->draw_f = draw_f;
    label->len = 0;
}

void label_set_position(label_t *label, uint16_t x, uint16_t y) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);
    (*label->draw_f)(label->text, label->len, x, y, label->size, label->color);

    label->x = x;
    label->y = y;
}

void label_clear(label_t *label) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);

    label->len = 0;
}

void label_set_color(label_t *label, uint16_t color) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, color);

    label->color = color;
}

void label_set_text(label_t *label, const char *text, uint8_t len) {
    uint8_t maxLen = len > label->len ? len : label->len;
    char write[len];

    for (uint8_t c = 0; c < maxLen; c++) {
        if(c < len && c < label->len) {
            if (text[c] == label->text[c]) {
                write[c] = ' ';
                label->text[c] = ' ';
            } else {
                write[c] = text[c];
            }
        } else if (c < len) {
            write[c] = text[c];
        }
    }

    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);
    (*label->draw_f)(write, len, label->x, label->y, label->size, label->color);

    uint8_t realLen = 0;
    for(uint8_t c=0; c<len; c++) {
        if(text[c] != ' ') {
            realLen = c+1;
        }
        label->text[c] = text[c];
    }
    label->len = realLen;
}


void label_set_number(label_t *label, int16_t num) {
    char buffer[6];
    char sign = num >= 0 ? '+' : '-';
    if(num < 0) {
        num *= -1;
    }
    if(num == 0) {
        buffer[0] = '0';
        label_set_text(label, buffer, 1);
        return;
    }

    for(uint8_t c=0; c<5; c++) {
        if(num != 0) {
            buffer[5 - c] = (char) ((num % 10) + '0');
            num /= 10;
        } else {
            if(sign == '-') {
                buffer[5 - c] = sign;
                label_set_text(label, buffer + (5 - c), c + 1);
            } else {
                label_set_text(label, buffer + (5 - c) + 1, c);
            }
            break;
        }
    }

}

void label_forceText(label_t *label, char* text, uint8_t len) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);
    (*label->draw_f)(text, len, label->x, label->y, label->size, label->color);

    for(uint8_t c=0; c<len; c++) {
        label->text[c] = text[c];
    }
    label->len = len;
}

void label_set_size(label_t *label, uint8_t size) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);
    (*label->draw_f)(label->text, label->len, label->x, label->y, size, label->color);

    label->size = size;
}

void label_update(label_t *label) {
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->background);
    (*label->draw_f)(label->text, label->len, label->x, label->y, label->size, label->color);
}

void label_append(label_t *label, const char *text, uint8_t addLen) {
    char newText[12];
    for(uint8_t c=0; c<addLen+label->len; c++) {
        if(c < label->len) {
            newText[c] = label->text[c];
        } else {
            newText[c] = text[c-label->len];
        }
    }
    label_set_text(label, newText, addLen + label->len);
}

void label_append_num(label_t * label, int num) {
    char buffer[6];
    char sign = num >= 0 ? '+' : '-';
    if(num < 0) {
        num *= -1;
    }
    if(num == 0) {
        buffer[0] = '0';
        label_append(label, buffer, 1);
        return;
    }

    for(uint8_t c=0; c<5; c++) {
        if(num != 0) {
            buffer[5 - c] = (char) ((num % 10) + '0');
            num /= 10;
        } else {
            if(sign == '-') {
                buffer[5 - c] = sign;
                label_append(label, buffer + (5 - c), c + 1);
            } else {
                label_append(label, buffer + (5-c) +1, c);
            }
            break;
        }
    }
}
