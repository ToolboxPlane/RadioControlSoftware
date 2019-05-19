/**
 * @file calibrate.c
 * @author paul
 * @date 19.05.19
 * @brief calibrate @TODO
 */

#include "calibrate.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/colors.h"
#include "../../View/Elements/button.h"
#include "../../View/strings.h"
#include "../controller.h"
#include "../../View/ui.h"
#include "../../View/colorconvert.h"
#include "../../View/materialColors.h"

static void init(void *buf) {
    ili9341_fillrect(0,10,240, 320-10, BACKGROUND_COLOR);
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);
    label_t *labels = (label_t *) &buttons[1];
    label_init(&labels[0], BACKGROUND_COLOR, &ui_drawLabel);
    label_set_position(&labels[0], 45, 30);
    label_set_size(&labels[0], 3);
    label_set_color(&labels[0], r8g8b8Tor5g6b5(BLACK));
    label_set_text(&labels[0], TR(string_calibrate0));
    label_init(&labels[0], BACKGROUND_COLOR, &ui_drawLabel);
    label_set_position(&labels[0], 30, 70);
    label_set_size(&labels[0], 3);
    label_set_color(&labels[0], r8g8b8Tor5g6b5(BLACK));
    label_set_text(&labels[0], TR(string_calibrate1));

    joystick_start_calibration(&joystick_left);
    joystick_start_calibration(&joystick_right);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return SETTINGS;
    }
    return CALIBRATE;
}

static void finish(void *buf) {
    joystick_end_calibration(&joystick_left, 0);
    joystick_end_calibration(&joystick_right, 4);
}

controller_screen_render_t controller_get_calibrate_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.update = 0;
    result.handle_event = &handle_event;
    result.finish = &finish;
    return result;
}
