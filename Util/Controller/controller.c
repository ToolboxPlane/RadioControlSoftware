/**
 * @file controller.c
 * @author paul
 * @date 12.05.19
 * @brief controller @TODO
 */

#include "controller.h"
#include "../View/ui.h"
#include "../../Drivers/stmpe610.h"
#include "../Model/model.h"
#include "../View/strings.h"

controller_page_t page = START;
joystick_t joystick_left, joystick_right;

void controller_init() {
    ui_init();
    stmpe610_init();
}

void controller_set_debug(uint8_t index, uint16_t val) {
    if(index < 6) {
        model_debug_vals[index] = val;
    }
}

int8_t controller_get_selection() {
    static int8_t lastSel = -1;
    if (stmpe610_buffer_empty()) {
        ui_button_highlight(lastSel, false);
        return lastSel =  -1;
    } else if(lastSel >= 0) {
        stmpe610_get_point();
        return -1;
    } else {
        tsPoint_t p = stmpe610_get_point();

        p.x = (uint16_t)((p.x - TS_MINX)/(TS_MAXX - TS_MINX) * 240);
        p.y = 320 - (uint16_t)((p.y - TS_MINY)/(TS_MAXY - TS_MINY) * 320);

        if (p.y < 15) {
            return -1;
        }

        lastSel = (int8_t)((p.y - 15) / 50);

        ui_button_highlight(lastSel, true);
        return lastSel;
    }
}

void controller_update_buttons() {
    switch (page) {
        case START:
            label_set_text(&ui_buttonLabel[0], TR(string_armDisarm));
            label_set_text(&ui_buttonLabel[1], TR(string_flightmodes));
            label_set_text(&ui_buttonLabel[2], TR(string_downlink));
            label_set_text(&ui_buttonLabel[3], TR(string_empty));
            label_set_text(&ui_buttonLabel[4], TR(string_settings));
            label_set_text(&ui_buttonLabel[5], TR(string_debug));
            break;
        case CALIBRATE:
            label_set_text(&ui_buttonLabel[0], TR(string_move));
            label_set_text(&ui_buttonLabel[1], TR(string_the));
            label_set_text(&ui_buttonLabel[2], TR(string_joysticks));
            label_set_text(&ui_buttonLabel[3], TR(string_empty));
            label_set_text(&ui_buttonLabel[4], TR(string_empty));
            label_set_text(&ui_buttonLabel[5], TR(string_finish));
            break;
        case SETTINGS:
            label_set_text(&ui_buttonLabel[0], TR(string_calibrate));
            if(model_get_serial_enabled()) {
                label_set_text(&ui_buttonLabel[1], TR(string_disableUSB));
            } else {
                label_set_text(&ui_buttonLabel[1], TR(string_enableUSB));
            }
            if(model_get_lora_enabled()) {
                label_set_text(&ui_buttonLabel[2], TR(string_disableLora));
            } else {
                label_set_text(&ui_buttonLabel[2], TR(string_enableLora));
            }
            label_set_text(&ui_buttonLabel[3], TR(string_empty));
            label_set_text(&ui_buttonLabel[4], TR(string_empty));
            label_set_text(&ui_buttonLabel[5], TR(string_back));
            break;
        case FLIGHTMODES:
            label_set_text(&ui_buttonLabel[0], TR(model_get_flightmode_string((model_flightmode_t) 0)));
            label_set_text(&ui_buttonLabel[1], TR(model_get_flightmode_string((model_flightmode_t) 1)));
            label_set_text(&ui_buttonLabel[2], TR(model_get_flightmode_string((model_flightmode_t) 2)));
            label_set_text(&ui_buttonLabel[3], TR(model_get_flightmode_string((model_flightmode_t) 3)));
            label_set_text(&ui_buttonLabel[4], TR(model_get_flightmode_string((model_flightmode_t) 4)));
            label_set_text(&ui_buttonLabel[5], TR(string_back));
            break;
        case DEBUG:
            label_set_text(&ui_buttonLabel[0], TR(string_log));
            label_set_text(&ui_buttonLabel[1], TR(string_version));
            label_set_text(&ui_buttonLabel[2], TR(string_compiledOn));
            label_set_text(&ui_buttonLabel[3], TR(string_compileDate));
            label_set_text(&ui_buttonLabel[4], TR(string_compileTime));
            label_set_text(&ui_buttonLabel[5], TR(string_back));
            break;
        case LOG:
            for(uint8_t c=0; c<6; c++) {
                label_set_number(&ui_buttonLabel[c],model_debug_vals[c]);
            }
            break;
        case DOWNLINK:
            label_set_text(&ui_buttonLabel[0], TR(string_snr));
            label_append_num(&ui_buttonLabel[0],model_snr);
            label_set_text(&ui_buttonLabel[1], TR(string_rssi));
            label_append_num(&ui_buttonLabel[1],model_rssi);
            label_set_text(&ui_buttonLabel[2], TR(string_sent));
            label_append_num(&ui_buttonLabel[2],model_sent);
            label_set_text(&ui_buttonLabel[3], TR(string_received));
            label_append_num(&ui_buttonLabel[3],model_received);
            label_set_text(&ui_buttonLabel[4], TR(string_empty));
            label_append_num(&ui_buttonLabel[4],model_remote_rssi);
            label_set_text(&ui_buttonLabel[5], TR(string_back));
            break;
        case RECEIVED_DATA:
            label_set_text(&ui_buttonLabel[0], TR(string_empty));
            label_set_text(&ui_buttonLabel[1], TR(string_empty));
            label_set_text(&ui_buttonLabel[2], TR(string_empty));
            label_set_text(&ui_buttonLabel[3], TR(string_empty));
            label_set_text(&ui_buttonLabel[4], TR(string_empty));
            label_set_text(&ui_buttonLabel[5], TR(string_back));
            break;
    }
}

void controller_handle_events(int8_t sel) {
    ui_update(model_armed, model_get_flightmode_string(model_flightmode));

    switch (page) {
        case START:
            switch (sel) {
                case 0:
                    model_armed = (uint8_t)!model_armed;
                    break;
                case 1:
                    page = FLIGHTMODES;
                    break;
                case 2:
                    page = DOWNLINK;
                    break;
                case 3:
                    break;
                case 4:
                    page = SETTINGS;
                    break;
                case 5:
                    page = DEBUG;
                    break;
                default:
                    break;
            }
            break;
        case CALIBRATE:
            switch (sel) {
                case 5:
                    joystick_end_calibration(&joystick_left, 0);
                    joystick_end_calibration(&joystick_right, 4);
                    page = SETTINGS;
                    break;
                default:
                    break;
            }
            break;
        case FLIGHTMODES:
            switch (sel) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    model_flightmode = (model_flightmode_t) sel;
                case 5:
                    page = START;
                    break;
            }
            break;
        case SETTINGS:
            switch (sel) {
                case 0:
                    joystick_start_calibration(&joystick_left);
                    joystick_start_calibration(&joystick_right);
                    page = CALIBRATE;
                    break;
                case 1:
                    model_set_serial_enabled(!model_get_serial_enabled());
                    break;
                case 2:
                    model_set_lora_enabled(!model_get_lora_enabled());
                    break;
                case 5:
                    page = START;
                    break;
            }
            break;
        case DOWNLINK:
            if(sel == 4) {
                page = RECEIVED_DATA;
            } else if(sel == 5) {
                page = START;
            }
            break;
        case RECEIVED_DATA:
            if(sel == 5) {
                page = DOWNLINK;
            }
            break;
        case DEBUG:
            switch (sel) {
                case 0:
                    page = LOG;
                    break;
                case 5:
                    page = START;
                    break;
            }
            break;
        case LOG:
            switch (sel) {
                case 5:
                    page = DEBUG;
                    break;
            }
            break;
        default:
            page = START;
            break;
    }
    controller_update_buttons();
}

