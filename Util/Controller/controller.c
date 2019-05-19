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
#include "screens/start.h"
#include "screens/flightmodes.h"
#include "screens/settings.h"

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

controller_screen_t page = START;
joystick_t joystick_left, joystick_right;

controller_screen_render_t screens[8];
controller_screen_t currScreen;
uint8_t screen_data[256];

void controller_init() {
    ui_init();
    stmpe610_init();

    screens[START] = controller_get_start_screen();
    screens[FLIGHTMODES] = controller_get_flightmodes_screen();
    screens[SETTINGS] = controller_get_settings_screen();

    currScreen = START;
    screens[currScreen].init(screen_data);
}

void controller_set_debug(uint8_t index, uint16_t val) {
    if(index < 6) {
        model_debug_vals[index] = val;
    }
}

void controller_update(void) {
    static bool clicked = false;
    if (stmpe610_buffer_empty()) {
        if (screens[currScreen].update) {
            screens[currScreen].update(screen_data);
        }
        clicked = false;
    } else if(clicked) {
        stmpe610_get_point();
    } else {
        clicked = true;
        tsPoint_t p = stmpe610_get_point();

        p.x = (uint16_t)((p.x - TS_MINX)/(TS_MAXX - TS_MINX) * 240);
        p.y = 320 - (uint16_t)((p.y - TS_MINY)/(TS_MAXY - TS_MINY) * 320);

        controller_screen_t next_screen = screens[currScreen].handle_event(screen_data, p.x, p.y);

        if (next_screen != currScreen) {
            currScreen = next_screen;
            screens[currScreen].init(screen_data);
        }
    }
    ui_update(model_armed, model_get_flightmode_string(model_flightmode));
}

