/**
 * @file settings.c
 * @author paul
 * @date 19.05.19
 * @brief settings @TODO
 */

#include "settings.h"
#include "../../View/Elements/button.h"
#include "../../View/colors.h"
#include "../../Model/model.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/strings.h"

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+0*50, 240-2*6, 40, TR(string_calibrate), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    if (model_get_lora_enabled()) {
        button_init(&buttons[1], 6, 20 + 1 * 50, 240 - 2 * 6, 40, TR(string_disable_lora),
                BUTTON_TEXT_COLOR, BUTTON_COLOR);
    } else {
        button_init(&buttons[1], 6, 20 + 1 * 50, 240 - 2 * 6, 40, TR(string_enable_lora),
                BUTTON_TEXT_COLOR, BUTTON_COLOR);
    }
    if (model_get_serial_enabled()) {
        button_init(&buttons[2], 6, 20 + 2 * 50, 240 - 2 * 6, 40, TR(string_disable_usb),
                    BUTTON_TEXT_COLOR, BUTTON_COLOR);
    } else {
        button_init(&buttons[2], 6, 20 + 2 * 50, 240 - 2 * 6, 40, TR(string_enable_usb),
                    BUTTON_TEXT_COLOR, BUTTON_COLOR);
    }
    button_init(&buttons[3], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return CALIBRATE;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        model_set_lora_enabled(!model_get_lora_enabled());
    } else if (button_is_clicked(&buttons[2], x, y)) {
        model_set_serial_enabled(!model_get_serial_enabled());
    } else if (button_is_clicked(&buttons[3], x, y)) {
        return START;
    }
    return SETTINGS;
}

void update(void *buf) {
    button_t *buttons = buf;
    if (model_get_lora_enabled()) {
        button_set_text(&buttons[1], TR(string_disable_lora));
    } else {
        button_set_text(&buttons[1], TR(string_enable_lora));
    }
    if (model_get_serial_enabled()) {
        button_set_text(&buttons[2], TR(string_disable_usb));
    } else {
        button_set_text(&buttons[2], TR(string_enable_usb));
    }
}

static void finish(void *buf) {
    ili9341_fillrect(6, 20+0*50, 240-2*6, 40, BACKGROUND_COLOR);
    ili9341_fillrect(6, 20+1*50, 240-2*6, 40, BACKGROUND_COLOR);
    ili9341_fillrect(6, 20+2*50, 240-2*6, 40, BACKGROUND_COLOR);
}

controller_screen_render_t controller_get_settings_screen(void) {
    controller_screen_render_t result;
    result.handle_event = &handle_event;
    result.update = &update;
    result.init = &init;
    result.finish = &finish;
    return result;
}
