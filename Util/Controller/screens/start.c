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

static void init(void *buf, uint16_t size) {
    button_t *buttons = buf;
    button_init(&buttons[0], 20+0*50, 6, 240-2*6, 40, ""
}

static controller_screen_t handle_event(void *buf, uint16_t size, uint16_t x,uint16_t y) {

}

controller_screen_render_t controller_get_start_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.update = 0;
    result.handle_event = &handle_event;
    return result;
}

