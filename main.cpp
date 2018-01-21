//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
extern "C" {
    #include "hal/ili9341.h"
    #include "hal/ili9341gfx.h"
    #include "hal/stmpe610.h"
    #include "drivers/adc.h"
    #include "drivers/uart.h"
}

#include ""
#include "Joystick.hpp"
#include "ui.h"
#include "controller.h"

Joystick joyLeft, joyRight;
int main() {
    controller::load();
    adc_init();
    uart_init(9600);
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(16);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    char buf[] = "Test\r\n";
    while(true) {
        controller::handleEvent(controller::getSelection());
        joyLeft.setXValue(adc_read(1));
        joyLeft.setYValue(adc_read(2));
        joyRight.setXValue(adc_read(4));
        joyRight.setYValue(adc_read(5));
        if(uart_available()) {
            uart_send(uart_read());
            uart_send('\n');
            uart_send('\r');
        }
    }
#pragma clang diagnostic pop
}
