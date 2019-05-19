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

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 20+0*50, 6, 240-2*6, 40, "Angle", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 20+1*50, 6, 240-2*6, 40, "Launch", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[2], 20+2*50, 6, 240-2*6, 40, "Land", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[3], 20+3*50, 6, 240-2*6, 40, "Hold", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[4], 20+4*50, 6, 240-2*6, 40, "Waypoint", BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[5], 20+5*50, 6, 240-2*6, 40, "Back", BUTTON_TEXT_COLOR, BUTTON_COLOR);
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

controller_screen_render_t controller_get_flightmodes_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.update = 0;
    result.handle_event = &handle_event;
    return result;
}

