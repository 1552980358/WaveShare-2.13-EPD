#ifndef WAVESHARE_2_13_EPD_COORDINATES_H
#define WAVESHARE_2_13_EPD_COORDINATES_H

#include <iostream>

typedef uint16_t axis_t;

typedef struct point {

    axis_t x;

    axis_t y;

} point_t;

typedef struct rect {

    point_t start;

    point_t end;

} rect_t;

#endif //WAVESHARE_2_13_EPD_COORDINATES_H
