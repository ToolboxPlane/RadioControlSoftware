//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include <avr/interrupt.h>

extern "C" {
    #include "hal/ili9341.h"
    #include "hal/ili9341gfx.h"
    #include "hal/stmpe610.h"
    #include "drivers/adc.h"
    #include "drivers/uart.h"
}

#include "hal/LoRa.h"
#include "RadioControlProtocol/rcLib.hpp"
#include "util/Joystick.hpp"
#include "ui.h"
#include "controller.h"

Joystick joyRight;
Joystick joyLeft;


int main() {
    rcLib::Package pkgOut(256, 8);
    rcLib::Package pkgUartIn;
    rcLib::Package pkgLoraIn;

    controller::load();
    adc_init();
    uart_init(9600);
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(16);

    LoRa.begin((long)434E6);

    rcLib::Package::transmitterId = 17;

    model::sent = model::received = 0;
    model::snr = model::rssi = 0;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {
        controller::handleEvent(controller::getSelection());
        joyLeft.setXValue(adc_read(1));
        joyLeft.setYValue(adc_read(2));
        joyRight.setXValue(adc_read(4));
        joyRight.setYValue(adc_read(5));

        pkgOut.setChannel(0, static_cast<uint16_t>(joyRight.getXValue() + 127));
        pkgOut.setChannel(1, static_cast<uint16_t>(joyRight.getYValue() + 127));
        pkgOut.setChannel(2, static_cast<uint16_t>(joyLeft.getXValue() + 127));
        pkgOut.setChannel(3, static_cast<uint16_t>(joyLeft.getYValue() + 127));
        pkgOut.setChannel(4, model::flightmode);
        pkgOut.setChannel(5, model::armed);
        pkgOut.setChannel(6, 0);
        pkgOut.setChannel(7, 0);
        uint8_t outLen = pkgOut.encode();

        if(model::serialEnabled()) {
            uart_send_buffer(pkgOut.getEncodedData(), outLen);
            while (uart_available()) {
                if(pkgUartIn.decode(uart_read())) {
                    controller::setDebug(0, pkgUartIn.getChannel(0));
                    controller::setDebug(1, pkgUartIn.getChannel(1));
                    controller::setDebug(2, pkgUartIn.getChannel(2));
                    controller::setDebug(3, pkgUartIn.getChannel(3));
                    controller::setDebug(4, 32);
                    controller::setDebug(5, 12);
                }
            }
        }
        if(model::loraEnabled()) {
            LoRa.beginPacket();
            LoRa.write(pkgOut.getEncodedData(), outLen);
            LoRa.endPacket();
            model::sent++;

            LoRa.receive();
            int size = LoRa.parsePacket();
            if (size) {
                model::rssi = LoRa.packetRssi();
                model::snr = (int8_t)LoRa.packetSnr();
                int read = 0;
                while((read = LoRa.read()) != -1) {
                    if(pkgLoraIn.decode((uint8_t)read)) {
                        model::received++;
                        model::remoteRssi = pkgLoraIn.getChannel(0);
                        model::remoteSnr = pkgLoraIn.getChannel(1);
                    }
                    uart_send((uint8_t)read);
                }
            }
        }
    }
#pragma clang diagnostic pop
}
