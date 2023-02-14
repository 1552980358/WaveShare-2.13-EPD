#include "pin.h"
#include "units.h"

void pin_mode(const pin_t &pin, const pin_mode_t &pin_mode) {
    pinMode(pin, pin_mode);
}

void pin_write(const pin_t &pin, const pin_data_t &byte) {
    digitalWrite(pin, byte);
}

pin_data_t pin_read(const pin_t &pin) {
    return digitalRead(pin);
}