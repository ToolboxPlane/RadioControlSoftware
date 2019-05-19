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

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 20+0*50, 6, 240-2*6, 40, "Arm/Disarm", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 20+1*50, 6, 240-2*6, 40, "Flightmodes", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[2], 20+2*50, 6, 240-2*6, 40, "Downlink", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[3], 20+5*50, 6, 240-2*6, 40, "Debug", BUTTON_TEXT_COLOR, BUTTON_COLOR);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return CALIBRATE;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        model_set_serial_enabled(!model_get_serial_enabled());
    } else if (button_is_clicked(&buttons[2], x, y)) {
        model_set_lora_enabled(!model_get_lora_enabled());
    } else if (button_is_clicked(&buttons[3], x, y)) {
        return START;
    }
    return START;
}

controller_screen_render_t controller_get_settings_screen(void) {
    controller_screen_render_t result;
    result.handle_event = &handle_event;
    result.update = 0;
    result.init = &init;
    return result;
}
