//
// Created by paul on 20.01.18.
//

#ifndef RADIOCONTROLSOFTWARE_STMPE610_H
#define RADIOCONTROLSOFTWARE_STMPE610_H

typedef struct TsPoint {
    int16_t x,y,z;
} tsPoint_t;

void stmpe610_pre_spi_init(void);
bool stmpe610_post_spi_init(void);
uint8_t stmpe610_touched(void);
uint8_t stmpe610_buffer_empty(void);
uint8_t stmpe610_buffer_size(void);
tsPoint_t stmpe610_get_point(void);

void stmpe610_write_register8(uint8_t reg, uint8_t val);
uint16_t stmpe610_read_register16(uint8_t reg);
uint8_t stmpe610_read_register8(uint8_t reg);
void stmpe610_read_data(uint16_t *x, uint16_t *y, uint8_t *z);
uint16_t stmpe610_get_version(void);



#endif //RADIOCONTROLSOFTWARE_STMPE610_H
