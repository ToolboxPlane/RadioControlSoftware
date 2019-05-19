/**
 * @file flightmodes.c
 * @author paul
 * @date 19.05.19
 * @brief flightmodes @TODO
 */

#include "flightmodes.h"
#include "../../View/Elements/button.h"
#include "../../View/colors.h"
#include "../../Model/model.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/strings.h"

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+0*50, 240-2*6, 40, TR(string_angle), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 6, 20+1*50, 240-2*6, 40, TR(string_launch), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[2], 6, 20+2*50, 240-2*6, 40, TR(string_land), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[3], 6, 20+3*50, 240-2*6, 40, TR(string_hold), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[4], 6, 20+4*50, 240-2*6, 40, TR(string_waypoint), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[5], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        model_flightmode = ANGLE;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        model_flightmode = LAUNCH;
    } else if (button_is_clicked(&buttons[2], x, y)) {
        model_flightmode = LAND;
    } else if (button_is_clicked(&buttons[3], x, y)) {
        model_flightmode = HOLD;
    } else if (button_is_clicked(&buttons[4], x, y)) {
        model_flightmode = WAYPOINT;
    } else if (button_is_clicked(&buttons[5], x, y)) {
        return START;
    }
    return FLIGHTMODES;
}

static void finish(void *buf) {
    for (uint8_t c=0; c<6; ++c) {
        ili9341_fillrect(6, 20 + c * 50, 240 - 2 * 6, 40, BACKGROUND_COLOR);
    }
}

controller_screen_render_t controller_get_flightmodes_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.update = 0;
    result.handle_event = &handle_event;
    result.finish = &finish;
    return result;
}

