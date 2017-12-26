#include "Arduino.h"
#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "src/RadioControlProtocol/rcLib.hpp"

#include "Joystick.hpp"
#include "model.h"
#include "controller.h"

bool orientation;

int receiveCount = 0;

Joystick joyLeft, joyRight;

RH_RF95 rf95(5);

rcLib::Package serialOut(1024,8), serialIn;

void setup() {
    Serial.begin(9600);
    rcLib::Package::transmitterId = 17;

    if (!rf95.init()){
      Serial.println("Radio init failed");  
    } else {
      Serial.println("Radio init success");
    }
    rf95.setFrequency(434.0);

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

    serialOut.setChannel(0, joyLeft.getXValue());
    serialOut.setChannel(1, joyLeft.getYValue());
    serialOut.setChannel(2, joyLeft.getButton());
    serialOut.setChannel(3, joyRight.getXValue());
    serialOut.setChannel(4, joyRight.getYValue());
    serialOut.setChannel(5, joyRight.getButton());
    serialOut.setChannel(6, model::flightmode);
    serialOut.setChannel(7, controller::page);
    uint16_t l = serialOut.encode();
    Serial.write(serialOut.getEncodedData(), l);

    if(Serial.available()) {
        if(serialIn.decode(Serial.read())) {
            for(int c=0; c<6; c++) {
                controller::setDebug(c,
                    serialIn.getChannel(c));
            }
        }
    }
   

    controller::handleEvent(controller::getSelection());


    //if (rf95.available()) {
        // Should be a message for us now
        /*uint8_t buf[1];
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
    //}
}


