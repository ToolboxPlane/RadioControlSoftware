/**
 * @file telemetry.c
 * @author paul
 * @date 19.05.19
 * @brief telemetry @TODO
 */

#include "telemetry.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/Elements/button.h"
#include "../../View/colors.h"
#include "../../View/strings.h"
#include "../../View/ui.h"
#include "../../View/colorconvert.h"
#include "../../View/materialColors.h"

static void init(void *buf) {
    ili9341_fillrect(0,10,240, 320-10, BACKGROUND_COLOR);
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    button_init(&buttons[1], 6, 20+4*50, 240-2*6, 40, TR(string_rf_info), BUTTON_TEXT_COLOR, BUTTON_COLOR);

    label_t *labels = (label_t *) &buttons[2];
    for (uint8_t c=0; c<8; ++c) {
        label_init(&labels[c], BACKGROUND_COLOR, &ui_drawLabel);
        label_set_position(&labels[c], 6, 20+20*c);
        label_set_size(&labels[c], 2);
        label_set_color(&labels[c], r8g8b8Tor5g6b5(BLACK));

        label_set_text(&labels[c], TR(string_channel));
        label_append_num(&labels[c], c);
        label_append(&labels[c], ": ", 2);
        label_append_num(&labels[c], 0);
    }
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return START;
    } else if (button_is_clicked(&buttons[1], x, y)) {
        return RFINFO;
    }
    return TELEMETRY;
}

static void update(void *buf) {
    button_t *buttons = buf;
    label_t *labels = (label_t *) &buttons[2];

    for (uint8_t c=0; c<8; ++c) {
        label_set_text(&labels[c], TR(string_channel));
        label_append_num(&labels[c], c);
        label_append(&labels[c], ": ", 2);
        label_append_num(&labels[c], 0);
    }
}

controller_screen_render_t controller_get_telemetry_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.handle_event = &handle_event;
    result.update = &update;
    result.finish = 0;
    return result;
}
