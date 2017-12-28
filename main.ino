#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "src/RadioControlProtocol/rcLib.hpp"

#include "Joystick.hpp"
#include "model.h"
#include "controller.h"

Joystick joyLeft, joyRight;

RH_RF95 rf95(5);

rcLib::Package serialOut(1024,8), serialIn;

void setup() {
    Serial.begin(9600);
    rcLib::Package::transmitterId = 17;

    if (!rf95.init()){
      Serial.println("Radio init failed");  
    }
    rf95.setFrequency(434.0);

    controller::load();
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(4);
}

void loop() {
    controller::handleEvent(controller::getSelection());

    joyLeft.setButton(analogRead(A0));
    joyLeft.setXValue(analogRead(A1));
    joyLeft.setYValue(analogRead(A2));
    joyRight.setButton(analogRead(A3));
    joyRight.setXValue(analogRead(A4));
    joyRight.setYValue(analogRead(A5));

    if(model::serialEnabled()) {
        serialOut.setChannel(0, (joyLeft.getXValue() + 127)*4);
        serialOut.setChannel(1, (joyLeft.getYValue() + 127)*4);
        serialOut.setChannel(2, joyLeft.getButton());
        serialOut.setChannel(3, (joyRight.getXValue() + 127)*4);
        serialOut.setChannel(4, (joyRight.getYValue() + 127)*4);
        serialOut.setChannel(5, joyRight.getButton());
        serialOut.setChannel(6, model::flightmode);
        serialOut.setChannel(7, controller::page);
        Serial.write(serialOut.getEncodedData(), serialOut.encode());

        if(Serial.available()) {
            if(serialIn.decode(Serial.read())) {
                if(serialIn.isChecksumCorrect()) {
                    for(int c=0; c<6; c++) {
                        controller::setDebug(c,
                            serialIn.getChannel(c));
                    }
                } else {
                    controller::setDebug(0, "Checksum");
                    controller::setDebug(1, "wrong!");
                }
            }
        }
    }
   
    if(model::loraEnabled()) {
        if (rf95.available()) {
            // Should be a message for us now
            uint8_t buf[1];
            uint8_t len = sizeof(buf);
            if (rf95.recv(buf, &len)) {
                //      RH_RF95::printBuffer("request: ", buf, len);
                // Serial.print("got request: ");
                // Serial.println((char *) buf);
                //      Serial.print("RSSI: ");
                //      Serial.println(rf95.lastRssi(), DEC);

                // Send a reply
                uint8_t data[] = "And hello back to you";
                rf95.send(data, sizeof(data));
                rf95.waitPacketSent();
                // Serial.println("Sent a reply");
            } else {
                // Serial.println("recv failed");
            }
        }
    }
}