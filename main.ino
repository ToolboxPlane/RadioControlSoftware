#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

#include "Joystick.hpp"
#include "lib.hpp"
#include "model.h"
#include "controller.h"

bool orientation;

int receiveCount = 0;

Joystick joyLeft, joyRight;
rcLib::Package receivePackage;

void setup() {
    Serial.begin(9600);

    orientation = analogRead(A0) < 32;    

    controller::load();

    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(4);
}

void loop() {
    if(orientation){
        joyLeft.setButton(analogRead(A0));
        joyLeft.setXValue(1024 - analogRead(A2));
        joyLeft.setYValue(analogRead(A1));

        joyRight.setButton(analogRead(A3));
        joyRight.setXValue(analogRead(A4));
        joyRight.setYValue(analogRead(A5));
    } else {
        joyLeft.setButton(analogRead(A5));
        joyLeft.setXValue(1024 - analogRead(A4));
        joyLeft.setYValue(analogRead(A3));

        joyRight.setButton(analogRead(A2));
        joyRight.setXValue(analogRead(A1));
        joyRight.setYValue(analogRead(A0));
    }

    if(Serial.available()){
        if(receivePackage.decode(Serial.read())){
            receiveCount++;
        }
    }

    controller::handleEvent(controller::getSelection());
}


