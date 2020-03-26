//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include <avr/interrupt.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include "HAL/adc.h"
#include "HAL/uart.h"
#include "Drivers/ili9341.h"
#include "Drivers/rcLib/rc_lib.h"
#include "Util/Controller/joystick.h"
#include "Util/Controller/controller.h"
#include "Util/Model/model.h"
#include "HAL/spi.h"

static rc_lib_package_t *pkg_to_send_lora = NULL;

void uart_callback(uint8_t data) {
    static rc_lib_package_t pkg_uart_in;
    if(rc_lib_decode(&pkg_uart_in, data)) {
        *pkg_to_send_lora = pkg_uart_in;
    }
}

int main(void) {
    cli();
    adc_init();
    uart_init(0, 115200, NONE, 1, &uart_callback);

    joystick_init(&joystick_left);
    joystick_init(&joystick_right);
    joystick_load_calibration(&joystick_left, 0);
    joystick_load_calibration(&joystick_right, 16);

    //LoRa.begin((long)434E6);
    sei();

    controller_init();
    model_init();
    rc_lib_transmitter_id = 17;
    rc_lib_package_t pkg_out, pkg_lora_in;
    rc_lib_init_rx(&pkg_lora_in);
    rc_lib_init_tx(&pkg_out, 256, 8);

    uint16_t mux = 0;

    while(true) {
        controller_update();
        joystick_set_x_value(&joystick_left, adc_read_sync(1));
        joystick_set_y_value(&joystick_left, adc_read_sync(2));
        joystick_set_x_value(&joystick_right, adc_read_sync(4));
        joystick_set_y_value(&joystick_right, adc_read_sync(5));

        pkg_out.channel_data[0] = (uint16_t)(-joystick_get_x_value(&joystick_right) + 127);
        pkg_out.channel_data[1] = (uint16_t)(joystick_get_y_value(&joystick_right) + 127);
        pkg_out.channel_data[2] = (uint16_t)(-joystick_get_x_value(&joystick_left) + 127);
        pkg_out.channel_data[3] = (uint16_t)(joystick_get_y_value(&joystick_left) + 127);
        pkg_out.channel_data[4] = model_flightmode;
        pkg_out.channel_data[5] = model_armed;
        pkg_out.channel_data[6] = 0;
        pkg_out.channel_data[7] = 0;
        uint8_t outLen = rc_lib_encode(&pkg_out);

        _delay_ms(10);

        mux += 1;
        if (mux == 5) {
            if (model_get_serial_enabled()) {
                uart_send_buf(0, pkg_out.buffer, outLen);
            }
        } else if (mux >= 10) {
            mux = 0;
            if(model_get_lora_enabled()) {
                /*LoRa.beginPacket();
                LoRa.write(pkg_out.buffer, outLen);
                LoRa.endPacket();
                model_sent++;*/

                /*if (pkg_to_send_lora != NULL) {
                    uint16_t len = rc_lib_encode(pkg_to_send_lora);
                    LoRa.beginPacket();
                    LoRa.write(pkg_to_send_lora->buffer, len);
                    LoRa.endPacket();
                    model_sent++;
                    pkg_to_send_lora = NULL;
                }*/

                /*LoRa.receive();
                int size = LoRa.parsePacket();
                if (size) {
                    model_rssi = LoRa.packetRssi();
                    model_snr = (int8_t)LoRa.packetSnr();
                    int read = 0;
                    while((read = LoRa.read()) != -1) {
                        if(rc_lib_decode(&pkg_lora_in, read)) {
                            model_received++;
                            model_remote_rssi = pkg_lora_in.channel_data[0];
                            model_remote_snr = pkg_lora_in.channel_data[1];
                            uint8_t channel_min = pkg_lora_in.channel_count < 8 ? pkg_lora_in.channel_count : 8;
                            for (uint8_t c=0; c < channel_min; ++c) {
                                model_receive_data[c] = pkg_lora_in.channel_data[c];
                            }
                        }
                        uart_send_byte(0, (uint8_t)read);
                    }
                }*/
            }
        }
    }
}

#pragma clang diagnostic pop
