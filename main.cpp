//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
extern "C" {
    #include "ili9341.h"
    #include "ili9341gfx.h"
    #include "stmpe610.h"
    #include "adc.h"
}

#include "Joystick.hpp"
#include "ui.h"
#include "controller.h"

Joystick joyLeft, joyRight;
int main() {
    controller::load();
    adc_init();
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(16);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {
        controller::handleEvent(controller::getSelection());
        joyLeft.setXValue(adc_read(1));
        joyLeft.setYValue(adc_read(2));
        joyRight.setXValue(adc_read(4));
        joyRight.setYValue(adc_read(5));
    }
#pragma clang diagnostic pop
}
