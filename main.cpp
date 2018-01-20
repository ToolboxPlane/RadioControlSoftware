//
// Created by paul on 20.01.18.
//
#include<avr/io.h>
#include<util/delay.h>
extern "C" {
    #include "ili9341.h"
    #include "ili9341gfx.h"
}

#include "ui.h"

int main() {
    //display_init();//display initial data
    ui::load();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {

    }
#pragma clang diagnostic pop
}
