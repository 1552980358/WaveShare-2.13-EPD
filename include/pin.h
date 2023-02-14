#ifndef WAVESHARE_2_13_EPD_PIN_H
#define WAVESHARE_2_13_EPD_PIN_H

#include "units.h"

#include <Arduino.h>

#define EPD_SCK_PIN  13
#define EPD_MOSI_PIN 14
#define EPD_CS_PIN   15
#define EPD_RST_PIN  26
#define EPD_DC_PIN   27
#define EPD_BUSY_PIN 25

typedef enum pin_mode {
    IN = INPUT,
    OUT = OUTPUT
} pin_mode_t;

typedef byte_t pin_t;
typedef byte_t pin_data_t;

void pin_mode(const pin_t &, const pin_mode_t &);

void pin_write(const pin_t &, const pin_data_t &);

pin_data_t pin_read(const pin_t &);

#endif //WAVESHARE_2_13_EPD_PIN_H
