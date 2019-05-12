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
    #include "Util/Controller/joystick.h"
    #include "Util/View/ui.h"
    #include "Util/Controller/controller.h"
    #include "Util/Model/model.h"
}

#include "Drivers/LoRa.h"

void uart_callback(uint8_t data) {
    static rc_lib_package_t pkg_uart_in;
    if(rc_lib_decode(&pkg_uart_in, data)) {
        controller_set_debug(0, pkg_uart_in.channel_data[0]);
        controller_set_debug(1, pkg_uart_in.channel_data[1]);
        controller_set_debug(2, pkg_uart_in.channel_data[2]);
        controller_set_debug(3, pkg_uart_in.channel_data[3]);
        controller_set_debug(4, 32);
        controller_set_debug(5, 12);
    }
}

int main() {
    cli();

    controller_load();
    adc_init();
    uart_init(0, 9600, &uart_callback);
    joystick_load_calibration(&joystick_left, 0);
    joystick_load_calibration(&joystick_right, 16);

    LoRa.begin((long)434E6);
    sei();

    sent = received = 0;
    snr = rssi = 0;

    rc_lib_package_t pkg_out, pkg_lora_in;
    pkg_out.resolution = 256;
    pkg_out.channel_count = 8;
    pkg_out.mesh = false;
    rc_lib_transmitter_id = 17;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {
        controller_handle_events(controller_get_selection());
        joystick_set_x_value(&joystick_left, adc_read_sync(1));
        joystick_set_y_value(&joystick_left, adc_read_sync(2));
        joystick_set_x_value(&joystick_right, adc_read_sync(4));
        joystick_set_y_value(&joystick_right, adc_read_sync(5));

        pkg_out.channel_data[0] = (uint16_t)(-joystick_get_x_value(&joystick_right) + 127);
        pkg_out.channel_data[1] = (uint16_t)(joystick_get_y_value(&joystick_right) + 127);
        pkg_out.channel_data[2] = (uint16_t)(-joystick_get_x_value(&joystick_left) + 127);
        pkg_out.channel_data[3] = (uint16_t)(joystick_get_y_value(&joystick_left) + 127);
        pkg_out.channel_data[4] = flightmode;
        pkg_out.channel_data[5] = armed;
        pkg_out.channel_data[6] = 0;
        pkg_out.channel_data[7] = 0;
        uint8_t outLen = rc_lib_encode(&pkg_out);

        if(serialEnabled()) {
            uart_send_buf(0, pkg_out.buffer, outLen);
        }

        if(loraEnabled()) {
            LoRa.beginPacket();
            LoRa.write(pkg_out.buffer, outLen);
            LoRa.endPacket();
            sent++;

            LoRa.receive();
            int size = LoRa.parsePacket();
            if (size) {
                rssi = LoRa.packetRssi();
                snr = (int8_t)LoRa.packetSnr();
                int read = 0;
                while((read = LoRa.read()) != -1) {
                    if(rc_lib_decode(&pkg_lora_in, read)) {
                        received++;
                        remoteRssi = pkg_lora_in.channel_data[0];
                        remoteSnr = pkg_lora_in.channel_data[1];
                    }
                    uart_send_byte(0, (uint8_t)read);
                }
            }
        }
        _delay_ms(10);
    }
#pragma clang diagnostic pop
}
