#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "src/RadioControlProtocol/rcLib.hpp"

#include "util/Joystick.hpp"
#include "model.h"
#include "controller.h"

Joystick joyLeft, joyRight;

RH_RF95 rf95(5);

rcLib::Package serialIn;
rcLib::Package pkgOut(256, 8);

void setup() {
  Serial.begin(9600);
  rcLib::Package::transmitterId = 17;

  if (!rf95.init()) {
    Serial.println("Radio init failed");
  }
  rf95.setFrequency(434.0);

  controller::load();

  digitalWrite(A0, INPUT_PULLUP);
  digitalWrite(A3, INPUT_PULLUP);
  joyLeft.loadConfiguration(0);
  joyRight.loadConfiguration(16);
}

void loop() {
  controller::handleEvent(controller::getSelection());

  joyLeft.setButton(analogRead(A0));
  joyLeft.setXValue(analogRead(A1));
  joyLeft.setYValue(analogRead(A2));
  joyRight.setButton(analogRead(A3));
  joyRight.setXValue(analogRead(A4));
  joyRight.setYValue(analogRead(A5));

  pkgOut.setChannel(joyLeft.getXChannel(), joyLeft.getXValue()+127);
  pkgOut.setChannel(joyLeft.getYChannel(), joyLeft.getYValue()+127);
  pkgOut.setChannel(joyLeft.getBtnChannel(), joyLeft.getButton());
  pkgOut.setChannel(joyRight.getXChannel(), joyRight.getXValue()+127);
  pkgOut.setChannel(joyRight.getYChannel(), joyRight.getYValue()+127);
  pkgOut.setChannel(joyRight.getBtnChannel(), joyRight.getButton());
  pkgOut.setChannel(model::armedChannnel, model::armed);
  pkgOut.setChannel(model::flightmodeChannel, model::flightmode);
  uint8_t outLen = pkgOut.encode();


  if (model::serialEnabled()) {
    Serial.write(pkgOut.getEncodedData(), outLen);

    if (Serial.available()) {
      if (serialIn.decode(Serial.read())) {
        if (serialIn.isChecksumCorrect()) {
          for (int c = 0; c < 6; c++) {
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

  if (model::loraEnabled()) {
    rf95.send(pkgOut.getEncodedData(), outLen);
    rf95.waitPacketSent();
  }
}
