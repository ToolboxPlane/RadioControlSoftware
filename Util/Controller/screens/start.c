/**
 * @file start.c
 * @author paul
 * @date 15.05.19
 * @brief start @TODO
 */

#include <stdint.h>
#include "start.h"
#include "../../View/Elements/button.h"
#include "../../View/ui.h"
#include "../../View/colors.h"
#include "../../Model/model.h"

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 20+0*50, 6, 240-2*6, 40, "Arm/Disarm", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 20+1*50, 6, 240-2*6, 40, "Flightmodes", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[2], 20+2*50, 6, 240-2*6, 40, "Downlink", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[3], 20+4*50, 6, 240-2*6, 40, "Settings", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[4], 20+5*50, 6, 240-2*6, 40, "Debug", BUTTON_TEXT_COLOR, BUTTON_COLOR);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        model_armed = !model_armed;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        return FLIGHTMODES;
    } else if (button_is_clicked(&buttons[2], x, y)) {
        return DOWNLINK;
    } else if (button_is_clicked(&buttons[3], x, y)) {
        return SETTINGS;
    } else if (button_is_clicked(&buttons[4], x, y)) {
        return DEBUG;
    }
    return START;
}

controller_screen_render_t controller_get_start_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.update = 0;
    result.handle_event = &handle_event;
    return result;
}

