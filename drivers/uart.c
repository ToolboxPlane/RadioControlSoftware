//
// Created by paul on 21.01.18.
//

#include "uart.h"
#include <avr/interrupt.h>
#include <stdbool.h>

volatile uint8_t recv_buf[UART_BUF_SIZE];
volatile uint8_t recv_head, recv_tail;

ISR(USART_RX_vect) {
    recv_buf[recv_head] = UDR0;
    recv_head = (recv_head+1)%UART_BUF_SIZE;
}

void uart_init(uint16_t baud) {
    recv_head = recv_tail = 0;

    UBRR0 = (uint16_t)(F_CPU/(16.0f*baud) - 1); // Baudrate
    UCSR0B = (1 << RXCIE0) |  (1 << RXEN0) | (1 << TXEN0); // Interupt, RX,TX Enable
    UCSR0C = (1 << UCSZ01) | (1 <<  UCSZ00); // 8 Data Bits

    sei();
}

void uart_send(uint8_t c) {
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_send_buffer(uint8_t *buf, uint8_t len) {
    for(uint8_t c=0; c<len; c++) {
        uart_send(buf[c]);
    }
}

bool uart_available() {
    return recv_head != recv_tail;
}

uint8_t uart_read() {
    uint8_t ret = recv_buf[recv_tail];
    recv_tail = (recv_tail+1)%UART_BUF_SIZE;
    return ret;
}
