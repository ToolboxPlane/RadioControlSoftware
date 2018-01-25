//
// Created by paul on 21.01.18.
//

#ifndef RADIOCONTROLSOFTWARE_UART_H
#define RADIOCONTROLSOFTWARE_UART_H

#include <avr/io.h>
#include <stdbool.h>

#define UART_BUF_SIZE 64

void uart_init(uint16_t baud);
void uart_send(uint8_t c);
void uart_send_buffer(uint8_t* buf,  uint8_t len);
bool uart_available();
uint8_t uart_read();

#endif //RADIOCONTROLSOFTWARE_UART_H
