/**
 * @file sx127x.h
 * @author paul
 * @date 26.03.20
 * Description here TODO
 */
#ifndef RADIOCONTROLSOFTWARE_SX127X_H
#define RADIOCONTROLSOFTWARE_SX127X_H

#include <stdint.h>
#include <stdbool.h>

void sx127x_pre_spi_init(volatile uint8_t *cs_ddr, volatile uint8_t *cs_port, uint8_t cs_bit);
bool sx127x_post_spi_init(uint32_t frequency);

void sx127x_transmit(uint8_t *data, uint8_t len);
bool sx127x_package_available(void);
uint8_t sx127x_wait_for_package(uint8_t *data, uint8_t len);

int16_t sx127x_rssi(void);
int8_t sx127x_snr(void);

#endif //RADIOCONTROLSOFTWARE_SX127X_H
