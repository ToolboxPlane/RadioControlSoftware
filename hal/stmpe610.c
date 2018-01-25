//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include <util/delay.h>
#include "stmpe610.h"

uint8_t spiIn() {
    SPDR = 0;

    //Wait until transmission complete
    while(!(SPSR & (1<<SPIF) ));

    // Return received data
    return(SPDR);
}

void spiOut(uint8_t x) {
    SPDR = x;
    while(!(SPSR & (1<<SPIF) ));
}
void stmpe610_init() {
    STMPE610_CS_DDR |= (1 << STMPE610_CS_BIT);
    STMPE610_CS_PORT |= (1 << STMPE610_CS_BIT);

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);//mode 0,fosc/4
    //SPSR |= (1 << SPI2X);//doubling spi speed.i.e final spi speed-fosc/2

    if (stmpe610_getVersion() != 0x811) {
        return;
    }
    stmpe610_writeRegister8(STMPE_SYS_CTRL1, STMPE_SYS_CTRL1_RESET);
    _delay_ms(10);

    for (uint8_t i=0; i<65; i++) {
        stmpe610_readRegister8(i);
    }

    stmpe610_writeRegister8(STMPE_SYS_CTRL2, 0x0); // turn on clocks!
    stmpe610_writeRegister8(STMPE_TSC_CTRL, STMPE_TSC_CTRL_XYZ | STMPE_TSC_CTRL_EN); // XYZ and enable!
    stmpe610_writeRegister8(STMPE_INT_EN, STMPE_INT_EN_TOUCHDET);
    stmpe610_writeRegister8(STMPE_ADC_CTRL1, STMPE_ADC_CTRL1_10BIT | (0x6 << 4)); // 96 clocks per conversion
    stmpe610_writeRegister8(STMPE_ADC_CTRL2, STMPE_ADC_CTRL2_6_5MHZ);
    stmpe610_writeRegister8(STMPE_TSC_CFG, STMPE_TSC_CFG_4SAMPLE | STMPE_TSC_CFG_DELAY_1MS | STMPE_TSC_CFG_SETTLE_5MS);
    stmpe610_writeRegister8(STMPE_TSC_FRACTION_Z, 0x6);
    stmpe610_writeRegister8(STMPE_FIFO_TH, 1);
    stmpe610_writeRegister8(STMPE_FIFO_STA, STMPE_FIFO_STA_RESET);
    stmpe610_writeRegister8(STMPE_FIFO_STA, 0);    // unreset
    stmpe610_writeRegister8(STMPE_TSC_I_DRIVE, STMPE_TSC_I_DRIVE_50MA);
    stmpe610_writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    stmpe610_writeRegister8(STMPE_INT_CTRL, STMPE_INT_CTRL_POL_HIGH | STMPE_INT_CTRL_ENABLE);
}

uint8_t stmpe610_touched() {
    return (stmpe610_readRegister8(STMPE_TSC_CTRL) & 0x80);

}

uint8_t stmpe610_buffer_empty() {
    return (stmpe610_readRegister8(STMPE_FIFO_STA) & STMPE_FIFO_STA_EMPTY);
}

uint8_t stmpe610_buffer_Size() {
    return stmpe610_readRegister8(STMPE_FIFO_SIZE);
}

tsPoint_t stmpe610_get_point() {
    uint16_t x, y;
    uint8_t z;
    stmpe610_readData(&x, &y, &z);
    return (tsPoint_t){x, y, z};
}

void stmpe610_writeRegister8(uint8_t reg, uint8_t val) {
    STMPE610_CS_PORT &= ~(1 << STMPE610_CS_BIT);
    _delay_us(5);//little delay
    spiOut(reg);
    spiOut(val);
    STMPE610_CS_PORT |= (1<<STMPE610_CS_BIT);
}

uint16_t stmpe610_readRegister16(uint8_t reg) {
    uint16_t x = 0;
    STMPE610_CS_PORT &= ~(1 << STMPE610_CS_BIT);
    _delay_us(5);//little delay
    spiOut(0x80 | reg);
    spiOut(0x00);
    x = spiIn();
    x<<=8;
    x |= spiIn();
    STMPE610_CS_PORT |= (1<<STMPE610_CS_BIT);
    return x;
}

uint8_t stmpe610_readRegister8(uint8_t reg) {
    STMPE610_CS_PORT &= ~(1 << STMPE610_CS_BIT);
    _delay_us(5);//little delay
    spiOut(0x80 | reg);
    spiOut(0x00);
    uint8_t x = spiIn();
    STMPE610_CS_PORT |= (1<<STMPE610_CS_BIT);
    return x;
}

void stmpe610_readData(uint16_t *x, uint16_t *y, uint8_t *z) {
    uint8_t data[4];

    for (uint8_t i=0; i<4; i++) {
        data[i] = stmpe610_readRegister8(0xD7); //SPI.transfer(0x00);
        // Serial.print("0x"); Serial.print(data[i], HEX); Serial.print(" / ");
    }
    *x = data[0];
    *x <<= 4;
    *x |= (data[1] >> 4);
    *y = data[1] & 0x0F;
    *y <<= 8;
    *y |= data[2];
    *z = data[3];

    if (stmpe610_buffer_empty()) {
        stmpe610_writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    }
}

uint16_t stmpe610_getVersion() {
    uint16_t v;
    //Serial.print("get version");
    v = stmpe610_readRegister8(0);
    v <<= 8;
    v |= stmpe610_readRegister8(1);
    //Serial.print("Version: 0x"); Serial.println(v, HEX);
    return v;
}

