/**
 * @file button.c
 * @author paul
 * @date 15.05.19
 * @brief button @TODO
 */

#include "button.h"
#include "../ui.h"
#include "../../../Drivers/ili9341.h"

void button_init(button_t *button, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
        const char *text, uint8_t text_len, uint16_t text_color, uint16_t color) {
    button->x = x;
    button->y = y;
    button->height = height;
    button->width = width;
    ili9341_fillrect(x,y,width,height, color);
    label_init(&button->label, color, &ui_draw_label);
    label_set_position(&button->label, x+8,y+10);
    label_set_color(&button->label, text_color);
    label_set_size(&button->label, 3);
    label_set_text(&button->label, text, text_len);
}

bool button_is_clicked(const button_t *button, uint16_t x, uint16_t y) {
    return button->x <= x && x <= button->x + button->width &&
            button->y <= y && y <= button->y + button->height;
}

void button_set_text(button_t *button, const char *text, uint8_t text_len) {
    label_set_text(&button->label, text, text_len);
}

