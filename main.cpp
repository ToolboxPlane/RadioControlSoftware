//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include <avr/interrupt.h>

extern "C" {
    #include "HAL/adc.h"
    #include "HAL/uart.h"
    #include "Drivers/ili9341.h"
    #include "Drivers/ili9341gfx.h"
    #include "Drivers/stmpe610.h"
    #include "Drivers/rcLib/rc_lib.h"
}

#include "Drivers/LoRa.h"
#include "Util/Joystick.hpp"
#include "ui.h"
#include "controller.h"

Joystick joyRight;
Joystick joyLeft;

void uart_callback(uint8_t data) {
    static rc_lib_package_t pkg_uart_in;
    if(rc_lib_decode(&pkg_uart_in, data)) {
        controller::setDebug(0, pkg_uart_in.channel_data[0]);
        controller::setDebug(1, pkg_uart_in.channel_data[1]);
        controller::setDebug(2, pkg_uart_in.channel_data[2]);
        controller::setDebug(3, pkg_uart_in.channel_data[3]);
        controller::setDebug(4, 32);
        controller::setDebug(5, 12);
    }
}

int main() {
    cli();

    controller::load();
    adc_init();
    uart_init(0, 9600, &uart_callback);
    joyLeft.loadConfiguration(0);
    joyRight.loadConfiguration(16);

    LoRa.begin((long)434E6);
    sei();

    model::sent = model::received = 0;
    model::snr = model::rssi = 0;

    rc_lib_package_t pkg_out, pkg_lora_in;
    pkg_out.resolution = 256;
    pkg_out.channel_count = 8;
    pkg_out.mesh = false;
    rc_lib_transmitter_id = 17;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {
        controller::handleEvent(controller::getSelection());
        joyLeft.setXValue(adc_read_sync(1));
        joyLeft.setYValue(adc_read_sync(2));
        joyRight.setXValue(adc_read_sync(4));
        joyRight.setYValue(adc_read_sync(5));

        pkg_out.channel_data[0] = static_cast<uint16_t>(-joyRight.getXValue() + 127);
        pkg_out.channel_data[1] = static_cast<uint16_t>(joyRight.getYValue() + 127);
        pkg_out.channel_data[2] = static_cast<uint16_t>(-joyLeft.getXValue() + 127);
        pkg_out.channel_data[3] = static_cast<uint16_t>(joyLeft.getYValue() + 127);
        pkg_out.channel_data[4] = model::flightmode;
        pkg_out.channel_data[5] = model::armed;
        pkg_out.channel_data[6] = 0;
        pkg_out.channel_data[7] = 0;
        uint8_t outLen = rc_lib_encode(&pkg_out);

        if(model::serialEnabled()) {
            uart_send_buf(0, pkg_out.buffer, outLen);
        }

        if(model::loraEnabled()) {
            LoRa.beginPacket();
            LoRa.write(pkg_out.buffer, outLen);
            LoRa.endPacket();
            model::sent++;

            LoRa.receive();
            int size = LoRa.parsePacket();
            if (size) {
                model::rssi = LoRa.packetRssi();
                model::snr = (int8_t)LoRa.packetSnr();
                int read = 0;
                while((read = LoRa.read()) != -1) {
                    if(rc_lib_decode(&pkg_lora_in, read)) {
                        model::received++;
                        model::remoteRssi = pkg_lora_in.channel_data[0];
                        model::remoteSnr = pkg_lora_in.channel_data[1];
                    }
                    uart_send_byte(0, (uint8_t)read);
                }
            }
        }
        _delay_ms(10);
    }
#pragma clang diagnostic pop
}
