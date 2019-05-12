/**
 * @file strings.c
 * @author paul
 * @date 12.05.19
 * @brief strings @TODO
 */
#include <stdint.h>
#include <avr/pgmspace.h>

char* getData(const char* addr) {
    static char data[12] = {' '};
    uint8_t c = 0;
    while ((data[c] = pgm_read_byte(addr + c++)));
    for(;c< sizeof(data);c++) {
        data[c] = ' ';
    }
    return data;
}

