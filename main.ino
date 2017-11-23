#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "rcLib.hpp"

#include "Joystick.hpp"
#include "model.h"
#include "controller.h"

bool orientation;

int receiveCount = 0;

Joystick joyLeft, joyRight;
rcLib::Package receivePackage;

RH_RF95 rf95(5);

void setup() {
    Serial.begin(9600);

    Serial.print("Compiled at:\t");
    Serial.println(__TIMESTAMP__);


    /*if (!rf95.init()){
      Serial.println("Radio init failed");  
    } else {
      Serial.println("Radio init success");
    }
    rf95.setFrequency(434.0);*/

    orientation = analogRead(A0) < 32;

    controller::load();

    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(4);
}

void loop() {
    if (orientation) {
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

    if (Serial.available()) {
        if (receivePackage.decode(Serial.read())) {
            receiveCount++;
        }
    }

    controller::handleEvent(controller::getSelection());


    if (rf95.available()) {
       /* // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (rf95.recv(buf, &len)) {
            //      RH_RF95::printBuffer("request: ", buf, len);
            Serial.print("got request: ");
            Serial.println((char *) buf);
            //      Serial.print("RSSI: ");
            //      Serial.println(rf95.lastRssi(), DEC);

            // Send a reply
            uint8_t data[] = "And hello back to you";
            rf95.send(data, sizeof(data));
            rf95.waitPacketSent();
            Serial.println("Sent a reply");
        } else {
            Serial.println("recv failed");
        }*/
    }
}


