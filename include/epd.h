#ifndef WAVESHARE_2_13_EPD_EPD_H
#define WAVESHARE_2_13_EPD_EPD_H

#include "units.h"

#define EPD_WIDTH 122
#define EPD_HEIGHT 250

byte_t REFRESH_FULL[] = {
        0x80, 0x4A, 0x40, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
        0x00, 0x00,0x40, 0x4A, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,0x80, 0x4A, 0x40, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x40, 0x4A, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x0F, 0x00, 0x00,
        0x0F, 0x00, 0x00, 0x02,0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00,0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
        0x00, 0x00, 0x00,0x22, 0x17, 0x41, 0x00, 0x32, 0x36
};

byte_t REFRESH_PART[] = {
        0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,
        0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x22,0x22,
        0x00,0x00,0x00,0x22,0x17,0x41,0x00,0x32,0x36,
};

void epd_setup();
void epd_clear();
void epd_draw_full(const byte_t *);
void epd_draw_base(const byte_t *);
void epd_draw_part(const byte_t *);

#endif //WAVESHARE_2_13_EPD_EPD_H
