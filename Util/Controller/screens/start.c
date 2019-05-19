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
#include "../../../Drivers/ili9341.h"
#include "../../View/strings.h"

static void init(void *buf) {
    ili9341_fillrect(0,10,240, 320-10, BACKGROUND_COLOR);
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+0*50, 240-2*6, 40, TR(string_arm_disarm), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 6, 20+1*50, 240-2*6, 40, TR(string_flightmodes), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[2], 6, 20+2*50, 240-2*6, 40, TR(string_telemetry), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[3], 6, 20+4*50, 240-2*6, 40, TR(string_settings), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[4], 6, 20+5*50, 240-2*6, 40, TR(string_debug), BUTTON_TEXT_COLOR, BUTTON_COLOR);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        model_armed = !model_armed;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        return FLIGHTMODES;
    } else if (button_is_clicked(&buttons[2], x, y)) {
        return TELEMETRY;
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
    result.finish = 0;
    return result;
}

