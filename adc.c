//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include "adc.h"

void adc_init() {
    ADCSRA = 1 << ADEN | 1 << ADPS2  | ADPS1; // Enabled, Prescaler 64
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = 1 << REFS0 | channel; // Internal Ref | Channel-Mux
    ADCSRA |= 1 << ADSC; // Start conversion
    while(ADCSRA & (1 << ADSC)); // conversion running
    return ADCL | ADCH << 8; // Low byte must be read first
}
