/**
 * @file sx127x.c
 * @author paul
 * @date 26.03.20
 * Description here TODO
 */
#include "sx127x.h"

#include <stdbool.h>
#include <util/delay.h>

#include "../HAL/spi.h"

#define SELECT (*_cs_port &= ~(1u << _cs_bit))
#define UNSELECT (*_cs_port |= (1u << _cs_bit))

#define READ 0x00u
#define WRITE 0x80u

#define RX_OFFSET 0x00
#define TX_OFFSET 0x80

static volatile uint8_t *_cs_ddr = 0;
static volatile uint8_t *_cs_port = 0;
static volatile uint8_t _cs_bit = 0;

static volatile bool ready = false;

void sx127x_spi_interrupt(void) {
    ready = true;
}

static void sx127x_blocking_write(uint8_t addr, const uint8_t *data, uint8_t len) {
    uint8_t buf[len + 1];
    buf[0] = addr | WRITE;
    for (uint8_t c=0; c<len; ++c) {
        buf[c+1] = data[c];
    }
    ready = false;
    SELECT;
    _delay_us(5);
    spi_tx_rx(buf, len+1, &sx127x_spi_interrupt);
    while (!ready);
    UNSELECT;
}

static void sx127x_blocking_read(uint8_t addr, uint8_t *data, uint8_t len) {
    uint8_t buf[len + 1];
    buf[0] = addr | READ;
    for (uint8_t c=1; c<len+1; ++c) {
        buf[c] = 0;
    }
    ready = false;
    SELECT;
    _delay_us(5);
    spi_tx_rx(buf, len+1, &sx127x_spi_interrupt);
    while (!ready);
    UNSELECT;
    for (uint8_t c=0; c<len; ++c) {
        data[c] = buf[c+1];
    }
}

static void sx127x_blocking_single_write(uint8_t addr, uint8_t data) {
    sx127x_blocking_write(addr, &data, 1);
}

static uint8_t sx127x_blocking_single_read(uint8_t addr) {
    uint8_t buf;
    sx127x_blocking_read(addr, &buf, 1);
    return buf;
}

void sx127x_blocking_fifo_write(uint8_t addr, const uint8_t *data, uint8_t len) {
    sx127x_blocking_single_write(0x0D, addr);
    sx127x_blocking_write(0x00, data, len);
}

void sx127x_blocking_fifo_read(uint8_t addr, uint8_t *data, uint8_t len) {
    sx127x_blocking_single_write(0x0D, addr);
    sx127x_blocking_read(0x00, data, len);
}

void sx127x_pre_spi_init(volatile uint8_t *cs_ddr, volatile uint8_t *cs_port, uint8_t cs_bit) {
    _cs_ddr = cs_ddr;
    _cs_port = cs_port;
    _cs_bit = cs_bit;

    *_cs_ddr |= (1u << _cs_bit);
    UNSELECT;
}


bool sx127x_post_spi_init(uint32_t frequency) {
    // Check version
    if (sx127x_blocking_single_read(0x42) != 0x12) {
        return false;
    }
    // Op-Mode: LoRA, FSK, LF-Mode, Sleep-Mode
    sx127x_blocking_single_write(0x01, 0b10000000);

    // Set Carrier Frequency (0x06 - 0x08)
    uint64_t frf = ((uint64_t)frequency << 19u) / 32000000u;
    uint8_t buf[3] = {frf >> 16u, frf >> 8u, frf >> 0u};
    sx127x_blocking_write(0x06, buf, 3);

    // Set Output Power to 15dbm
    sx127x_blocking_single_write(0x09, 0b01111111);

    // Set LNA-Gain to highest gain and enable boost
    sx127x_blocking_single_write(0x0C, 0b00100011);

    // Modem Config 2: Set Bandwidth to 125kHz, Coding Rate 4/5, Explicit Header
    sx127x_blocking_single_write(0x1D, 0b01110010);

    // Modem Config 2: Set Spreading Factor to 128 chips/symbol, CRC on
    sx127x_blocking_single_write(0x1E, 0b01110100);

    // Modem Config 3: Enable automatic gain calculation, enable low data rate optimization ("long symbols")
    sx127x_blocking_single_write(0x26, 0b00001000);

    // Enable optimization for 500kHz Bandwidth, see errata
    //sx127x_blocking_single_write(0x36, 0x02);
    //sx127x_blocking_single_write(0x3A, 0x7F);

    // Set maximum payload length to 127 (half of the FIFO is used for TX, half for RX)
    sx127x_blocking_single_write(0x23, 127);

    // Set in (Continuous) RX mode
    sx127x_blocking_single_write(0x01, 0b10000101);

    return true;
}

void sx127x_transmit(uint8_t *data, uint8_t len) {
    if (len > 127) {
        return;
    }

    sx127x_blocking_single_write(0x01, 0b10000001); // Set in Standby mode

    sx127x_blocking_single_write(0x12, 1u << 3u); // Clear TX done interrupt flags
    sx127x_blocking_single_write(0x22, len + 4); // Write FIFO len
    sx127x_blocking_single_write(0x0E, TX_OFFSET); // Set the TX Buffer Start Address

    // Write header + data
    uint8_t header[4] = {255, 0, 0, 0};
    sx127x_blocking_fifo_write(TX_OFFSET, header, 4);
    sx127x_blocking_fifo_write(TX_OFFSET + 4, data, len);

    // Set in TX mode
    sx127x_blocking_single_write(0x01, 0b10000011);

    // Wait for transmission complete
    while (!(sx127x_blocking_single_read(0x12) & (1u << 3u)));

    sx127x_blocking_single_write(0x12, 1u << 3u); // Clear interrupt flags
    sx127x_blocking_single_write(0x01, 0b10000101); // Set in (Continuous) RX mode
}

bool sx127x_package_available(void) {
    sx127x_blocking_single_write(0x01, 0b10000101); // Set in (Continuous) RX mode
    uint8_t irq_flags = sx127x_blocking_single_read(0x12);
    return irq_flags & (1u << 6u);
}

uint8_t sx127x_wait_for_package(uint8_t *data, uint8_t len) {
    sx127x_blocking_single_write(0x01, 0b10000101); // Set in (Continuous) RX mode

    // Wait for any RX event
    uint8_t irq_flags = sx127x_blocking_single_read(0x12);
    while (!(irq_flags & (0b111u << 5u))) {
        irq_flags = sx127x_blocking_single_read(0x12);
    }

    // Check if not RX done
    if (!(irq_flags & (1u << 6u))) {
        return 0;
    }

    sx127x_blocking_single_write(0x12, 0b111u << 5u); // Clear interrupt flags

    uint8_t rx_fifo_ptr = sx127x_blocking_single_read(0x25);
    uint8_t number_bytes = rx_fifo_ptr - RX_OFFSET;

    uint8_t buf[number_bytes];
    sx127x_blocking_fifo_read(RX_OFFSET, buf, number_bytes);

    uint8_t min_len = number_bytes < len ? number_bytes : len;

    if (min_len <= 4) {
        return 0;
    }

    for (uint8_t c=4; c<min_len; ++c) {
        data[c-4] = buf[c];
    }

    return min_len - 4;
}

int16_t sx127x_rssi(void) {
    return (int16_t)sx127x_blocking_single_read(0x1B) - 157;
}


int8_t sx127x_snr(void) {
    return (int8_t)sx127x_blocking_single_read(0x19) / 4;
}

