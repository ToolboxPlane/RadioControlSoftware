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
#include "Screens/start.h"
#include "Screens/flightmodes.h"
#include "Screens/settings.h"
#include "Screens/calibrate.h"
#include "Screens/rfinfo.h"
#include "Screens/telemetry.h"
#include "Screens/debug.h"
#include "../../Drivers/ili9341.h"
#include "../View/colors.h"
#include "../../HAL/spi.h"
#include "../../Drivers/sx127x.h"

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

joystick_t joystick_left, joystick_right;

controller_screen_render_t screens[CONTROLLER_SCREEN_T_LEN];
controller_screen_t currScreen;
uint8_t screen_data[256];

void controller_init() {
    ili9341_pre_spi_init();
    stmpe610_pre_spi_init();
    sx127x_pre_spi_init(&DDRD, &PORTD, 5);
    spi_init(false, DIV_16);
    ili9341_post_spi_init();
    ui_init();

    if (!stmpe610_post_spi_init()) {
        //ui_show_error(string_error_touch);
    }

    if (!sx127x_post_spi_init(434E6)) {
        ui_show_error(string_error_lora);
    }


    screens[START] = controller_get_start_screen();
    screens[FLIGHTMODES] = controller_get_flightmodes_screen();
    screens[SETTINGS] = controller_get_settings_screen();
    screens[CALIBRATE] = controller_get_calibrate_screen();
    screens[RFINFO] = controller_get_rfinfo_screen();
    screens[TELEMETRY] = controller_get_telemetry_screen();
    screens[DEBUG] = controller_get_debug_screen();

    currScreen = START;
    screens[currScreen].init(screen_data);
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
            if (screens[currScreen].finish) {
                screens[currScreen].finish(screen_data);
            } else {
                ili9341_fillrect(0,10,240, 320-10, BACKGROUND_COLOR);
            }
            currScreen = next_screen;
            screens[currScreen].init(screen_data);
        }
    }
    ui_update(model_armed, model_get_flightmode_string(model_flightmode));
}

