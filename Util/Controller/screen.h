/**
 * @file screen.h
 * @author paul
 * @date 15.05.19
 * @brief screen @TODO
 */

#ifndef RADIOCONTROLSOFTWARE_SCREEN_H
#define RADIOCONTROLSOFTWARE_SCREEN_H

#include <stdint.h>

typedef enum {
    START = 0,
    CALIBRATE = 1,
    FLIGHTMODES = 2,
    SETTINGS = 3,
    DEBUG = 4,
    RFINFO = 5,
    TELEMETRY = 6,
    CONTROLLER_SCREEN_T_LEN
} controller_screen_t;

typedef struct {
    void (*init)(void*);
    void (*update)(void*);
    controller_screen_t (*handle_event)(void*,uint16_t,uint16_t);
    void (*finish)(void*);
} controller_screen_render_t;

#endif //RADIOCONTROLSOFTWARE_SCREEN_H
