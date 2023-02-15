#ifndef WAVESHARE_2_13_EPD_EPD_H
#define WAVESHARE_2_13_EPD_EPD_H

#include "units.h"

#define EPD_WIDTH 122
#define EPD_HEIGHT 250

void epd_setup();
void epd_clear();
void epd_draw_full(const byte_t *);
void epd_draw_base(const byte_t *);
void epd_draw_part(const byte_t *);

#endif //WAVESHARE_2_13_EPD_EPD_H
