/**
 * @file downlink.c
 * @author paul
 * @date 19.05.19
 * @brief downlink @TODO
 */

#include "rfinfo.h"
#include "../../../Drivers/ili9341.h"
#include "../../View/colors.h"
#include "../../View/Elements/button.h"
#include "../../View/strings.h"
#include "../../View/ui.h"
#include "../../View/colorconvert.h"
#include "../../View/materialColors.h"
#include "../../Model/model.h"

static void init(void *buf) {
    button_t *buttons = buf;
    button_init(&buttons[0], 6, 20+5*50, 240-2*6, 40, TR(string_back), BUTTON_TEXT_COLOR, BUTTON_COLOR);

    label_t *labels = (label_t *) &buttons[1];
    for (uint8_t c=0; c<6; ++c) {
        label_init(&labels[c], BACKGROUND_COLOR, &ui_drawLabel);
        label_set_position(&labels[c], 6, 20+30*c);
        label_set_size(&labels[c], 2);
        label_set_color(&labels[c], r8g8b8Tor5g6b5(BLACK));
    }
    label_set_text(&labels[0], TR(string_snr));
    label_append_num(&labels[0], model_snr);
    label_set_text(&labels[1], TR(string_rssi));
    label_append_num(&labels[1], model_rssi);
    label_set_text(&labels[2], TR(string_sent));
    label_append_num(&labels[2], model_sent);
    label_set_text(&labels[3], TR(string_received));
    label_append_num(&labels[3], model_received);
    label_set_text(&labels[4], TR(string_rssi_remote));
    label_append_num(&labels[4], model_remote_rssi);
    label_set_text(&labels[5], TR(string_snr_remote));
    label_append_num(&labels[5], model_remote_snr);
}

static controller_screen_t handle_event(void *buf, uint16_t x,uint16_t y) {
    button_t *buttons = buf;
    if (button_is_clicked(&buttons[0], x, y)) {
        return TELEMETRY;
    }
    return RFINFO;
}

static void update(void *buf) {
    button_t *buttons = buf;
    label_t *labels = (label_t *) &buttons[1];

    label_set_text(&labels[0], TR(string_snr));
    label_append_num(&labels[0], model_snr);
    label_set_text(&labels[1], TR(string_rssi));
    label_append_num(&labels[1], model_rssi);
    label_set_text(&labels[2], TR(string_sent));
    label_append_num(&labels[2], model_sent);
    label_set_text(&labels[3], TR(string_received));
    label_append_num(&labels[3], model_received);
    label_set_text(&labels[4], TR(string_rssi_remote));
    label_append_num(&labels[4], model_remote_rssi);
    label_set_text(&labels[5], TR(string_snr_remote));
    label_append_num(&labels[5], model_remote_snr);
}

static void finish(void *buf) {
    button_t *buttons = buf;
    ili9341_fillrect(6, 20+5*50, 240-2*6, 40, BACKGROUND_COLOR);

    label_t *labels = (label_t *) &buttons[1];
    for (uint8_t c=0; c<6; ++c) {
        label_set_color(&labels[c], BACKGROUND_COLOR);
    }
}

controller_screen_render_t controller_get_rfinfo_screen(void) {
    controller_screen_render_t result;
    result.init = &init;
    result.handle_event = &handle_event;
    result.update = &update;
    result.finish = &finish;
    return result;
}
