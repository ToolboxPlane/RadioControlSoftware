//
// Created by paul on 20.01.18.
//
#include<avr/io.h>
#include<util/delay.h>
extern "C" {
    #include "ili9341.h"
    #include "ili9341gfx.h"
    #include "stmpe610.h"
}

#include "Joystick.hpp"
#include "ui.h"
#include "controller.h"

Joystick joyLeft, joyRight;
int main() {
    controller::load();
    //digitalWrite(A0, INPUT_PULLUP);
    //digitalWrite(A3, INPUT_PULLUP);//
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(16);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    char pressed[] = "Pressed";
    char npressed[] = "Not";
    while(true) {
        controller::handleEvent(controller::getSelection());
    }
#pragma clang diagnostic pop
}
