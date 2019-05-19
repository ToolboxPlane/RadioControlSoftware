/**
 * @file debug.c
 * @author paul
 * @date 19.05.19
 * @brief debug @TODO
 */

#include "debug.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/Elements/button.h"
#include "../../View/colors.h"
#include "../../View/strings.h"
#include "../../View/ui.h"
#include "../../View/colorconvert.h"
#include "../../View/materialColors.h"

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);

    label_t *labels = (label_t *) &buttons[1];
    for (uint8_t c=0; c<4; ++c) {
        label_init(&labels[c], BACKGROUND_COLOR, &ui_drawLabel);
        label_set_position(&labels[c], 6, 20+30*c);
        label_set_size(&labels[c], 2);
        label_set_color(&labels[c], r8g8b8Tor5g6b5(BLACK));
    }
    label_set_text(&labels[0], TR(string_version));
    label_set_text(&labels[1], TR(string_compiled_on));
    label_set_text(&labels[2], TR(string_compile_date));
    label_set_text(&labels[3], TR(string_compile_time));
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return START;
    }
    return DEBUG;
}

controller_screen_render_t controller_get_debug_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.handle_event = handle_event;
    result.finish = 0;
    result.update = 0;
    return result;
}
