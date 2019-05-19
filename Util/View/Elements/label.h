#ifndef RADIOCONTROLSOFTWARE_LABEL_H
#define RADIOCONTROLSOFTWARE_LABEL_H

#include <stdint.h>

typedef void (*draw_f_t)(const char*, uint8_t, uint16_t, uint16_t, uint8_t, uint16_t);

typedef struct {
    char text[12];
    uint8_t len;
    uint16_t x, y;
    uint16_t color;
    uint8_t size;
    uint16_t background;
    draw_f_t draw_f;
} label_t;

void label_init(label_t *label, uint16_t background, draw_f_t draw_f);
void label_set_position(label_t *label, uint16_t x, uint16_t y);
void label_set_text(label_t *label, const char *text, uint8_t len);
void label_append(label_t *label, const char* text, uint8_t addLen);
void label_append_num(label_t *label, int number);
void label_set_number(label_t *label, int16_t num);
void label_clear(label_t *label);
void label_set_color(label_t *label, uint16_t color);
void label_set_size(label_t *label, uint8_t size);
void label_update(label_t *label);

#endif //SMARTWATCH2_LABEL_H
