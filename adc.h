//
// Created by paul on 20.01.18.
//

#ifndef RADIOCONTROLSOFTWARE_ADC_H
#define RADIOCONTROLSOFTWARE_ADC_H

#include <stdint.h>

void adc_init();
uint16_t adc_read(uint8_t channel);

#endif //RADIOCONTROLSOFTWARE_ADC_H
