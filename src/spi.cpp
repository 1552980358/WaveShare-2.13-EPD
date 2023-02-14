#include "../include/spi.h"
#include "../include/pin.h"

#define SPI_SET 1
#define SPI_RESET 0

void spi_write_byte(byte_t dat) {
    pin_write(EPD_CS_PIN, SPI_RESET);
    for (int i = 0; i < 8; ++i) {
        pin_write(EPD_MOSI_PIN,
                  !(dat & 0x80) ? SPI_RESET : SPI_SET
        );
        dat <<= 1;
        pin_write(EPD_SCK_PIN, SPI_SET);
        pin_write(EPD_SCK_PIN, SPI_RESET);
    }
    pin_write(EPD_CS_PIN, SPI_SET);
}