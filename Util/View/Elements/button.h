/**
 * @file button.h
 * @author paul
 * @date 15.05.19
 * @brief button @TODO
 */

#ifndef RADIOCONTROLSOFTWARE_BUTTON_H
#define RADIOCONTROLSOFTWARE_BUTTON_H

#include <stdbool.h>
#include "label.h"

typedef struct {
   label_t label;
   uint16_t x,y,width,height;
} button_t;

void button_init(button_t *button, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
        const char *text, uint8_t text_len, uint16_t text_color, uint16_t color);
void button_set_text(button_t *button, const char *text, uint8_t text_len);
bool button_is_clicked(const button_t *button, uint16_t x, uint16_t y);

#endif //RADIOCONTROLSOFTWARE_BUTTON_H
