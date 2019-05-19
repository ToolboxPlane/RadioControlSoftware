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
    LOG = 5,
    DOWNLINK = 6,
    RECEIVED_DATA = 7
} controller_screen_t;

typedef struct {
    void (*init)(void*);
    void (*update)(void*);
    controller_screen_t (*handle_event)(void*,uint16_t,uint16_t);
} controller_screen_render_t;

#endif //RADIOCONTROLSOFTWARE_SCREEN_H
