#ifndef ILI9341_H
#define ILI9341_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <limits.h>
#include <inttypes.h>

/*
 * Arduino Pins:
 * DC: 3 -> PD3
 * CS: 10 -> PB2
 */

#define DC_DDR DDRD
#define DC_PORT PORTD
#define DC_BIT 3

#define CS_DDR DDRB
#define CS_PORT PORTB
#define CS_BIT 2

#define ILI9341_TFTHEIGHT 240
#define ILI9341_TFTWIDTH 320


void ili9341_spi_init(void);
void ili9341_spi_send(unsigned char spi_data);
void ili9341_writecommand8(uint8_t com);
void ili9341_writedata8(uint8_t data);
void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void ili9341_init(void);
void ili9341_pushcolour(uint16_t colour);
void ili9341_clear(uint16_t colour);
void ili9341_drawpixel(uint16_t x3,uint16_t y3,uint16_t colour1);
void ili9341_drawvline(uint16_t x,uint16_t y,uint16_t h,uint16_t colour);
void ili9341_drawhline(uint16_t x,uint16_t y,uint16_t w,uint16_t colour);
void ili9341_fillrect(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour);
void ili9341_setRotation(uint8_t x);
#endif

