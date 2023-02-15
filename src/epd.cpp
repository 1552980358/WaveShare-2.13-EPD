#include "coordinates.h"
#include "epd.h"
#include "pin.h"
#include "spi.h"

void epd_reset();
void epd_wait_busy();
void epd_lut_by_host(const byte_t *);
void epd_turn_on_full();
void epd_turn_on_part();
void epd_set_windows(const rect_t &);
void epd_set_cursor(const point_t &);

void epd_send_cmd(const byte_t &);
void epd_send_data(const byte_t &);

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

void epd_setup() {
    // Init pin mode
    pin_mode(EPD_BUSY_PIN, IN);
    pin_mode(EPD_RST_PIN, OUT);
    pin_mode(EPD_DC_PIN, OUT);
    pin_mode(EPD_SCK_PIN, OUT);
    pin_mode(EPD_MOSI_PIN, OUT);
    pin_mode(EPD_CS_PIN, OUT);

    // Init pin value
    pin_write(EPD_CS_PIN, HIGH);
    pin_write(EPD_SCK_PIN, LOW);

    epd_reset();
    delay(100);

    // SWRESET;
    epd_wait_busy();
    epd_send_cmd(0x12);
    epd_wait_busy();

    // Driver output control
    epd_send_cmd(0x01);
    epd_send_data(0xf9);
    epd_send_data(0x00);
    epd_send_data(0x00);

    //data entry mode
    epd_send_cmd(0x11);
    epd_send_data(0x03);
    epd_set_windows(rect { point { 0, 0 }, point { EPD_WIDTH - 1, EPD_HEIGHT - 1 } });
    epd_set_cursor(point_t {0, 0 });

    // BorderWaveFrom
    epd_send_cmd(0x3C);
    epd_send_data(0x05);

    // Display update control
    epd_send_cmd(0x21);
    epd_send_data(0x00);
    epd_send_data(0x80);

    // Read built-in temperature sensor
    epd_send_cmd(0x18);
    epd_send_data(0x80);

    epd_wait_busy();
    epd_lut_by_host(REFRESH_FULL);
}

const auto width = EPD_WIDTH / 8 + 1;
const auto height = EPD_HEIGHT;

void epd_clear() {
    epd_send_cmd(0x24);
    for (auto i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            epd_send_data(0xFF);
        }
    }
    epd_send_cmd(0x26);
    for (auto i = 0; i < height; ++i) {
        for (auto j = 0; j < width; ++j) {
            epd_send_data(0xFF);
        }
    }
    epd_turn_on_full();
}

void epd_draw_full(const byte_t *image) {
    epd_send_cmd(0x24);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            epd_send_data(image[i + j * width]);
        }
    }
    epd_turn_on_full();
}

void epd_draw_base(const byte_t *image) {
    epd_send_cmd(0x24);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            epd_send_data(image[i + j * width]);
        }
    }
    epd_send_cmd(0x26);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            epd_send_data(image[i + j * width]);
        }
    }
    epd_turn_on_full();
}

void epd_draw_part(const byte_t *image) {
    pin_write(EPD_RST_PIN, LOW);
    delay(1);
    pin_write(EPD_RST_PIN, HIGH);

    epd_lut_by_host(REFRESH_PART);

    epd_send_cmd(0x37);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x40);  ///RAM Ping-Pong enable
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);
    epd_send_data(0x00);

    // BorderWaveFrom
    epd_send_cmd(0x3C);
    epd_send_data(0x80);

    epd_send_cmd(0x22);     // Display Update Sequence Option
    epd_send_data(0xC0);     // Enable clock and  Enable analog
    epd_send_cmd(0x20);     // Activate Display Update Sequence
    epd_wait_busy();

    epd_set_windows(rect_t { 0, 0, EPD_WIDTH - 1, EPD_HEIGHT - 1 });
    epd_set_cursor(point_t { 0, 0 });

    epd_send_cmd(0x24);
    for (auto i = 0; i < height; ++i) {
        for (auto j = 0; j < width; ++j) {
            epd_send_data(image[i + j * width]);
        }
    }
    epd_turn_on_part();
}

void epd_reset() {
    pin_write(EPD_RST_PIN, HIGH);
    delay(20);
    pin_write(EPD_RST_PIN, LOW);
    delay(2);
    pin_write(EPD_RST_PIN, HIGH);
    delay(20);
}

void epd_wait_busy() {
    while (pin_read(EPD_BUSY_PIN));
    delay(10);
}

void epd_lut(const byte_t *lut) {
    epd_send_cmd(0x32);
    for (int i = 0; i < 153; ++i) {
        epd_send_data(lut[i]);
    }
    epd_wait_busy();
}

void epd_lut_by_host(const byte_t *lut) {
    epd_lut(lut);                        //lut
    epd_send_cmd(0x3f);
    epd_send_data(*(lut + 153));
    epd_send_cmd(0x03);            // gate voltage
    epd_send_data(*(lut + 154));
    epd_send_cmd(0x04);            // source voltage
    epd_send_data(*(lut + 155));    // VSH
    epd_send_data(*(lut + 156));    // VSH2
    epd_send_data(*(lut + 157));    // VSL
    epd_send_cmd(0x2c);            // VCOM
    epd_send_data(*(lut + 158));
}

void epd_set_windows(const rect_t &rect) {
    // SET_RAM_X_ADDRESS_START_END_POSITION
    epd_send_cmd(0x44);
    epd_send_data((rect.start.x >> 3) & 0xFF);
    epd_send_data((rect.end.x >> 3) & 0xFF);

    // SET_RAM_Y_ADDRESS_START_END_POSITION
    epd_send_cmd(0x45);
    epd_send_data(rect.start.y & 0xFF);
    epd_send_data((rect.start.y >> 8) & 0xFF);
    epd_send_data(rect.end.y & 0xFF);
    epd_send_data((rect.end.y >> 8) & 0xFF);
}

void epd_set_cursor(const point_t &point) {
    epd_send_cmd(0x4E);     // SET_RAM_X_ADDRESS_COUNTER
    epd_send_data(point.x & 0xFF);

    epd_send_cmd(0x4F);     // SET_RAM_Y_ADDRESS_COUNTER
    epd_send_data(point.y & 0xFF);
    epd_send_data((point.y >> 8) & 0xFF);
}

#define DISPLAY_TURN_ON_MODE_FULL 0xc7
#define DISPLAY_TURN_ON_MODE_PART 0x0f
void epd_turn_on_with_mode(const byte_t &mode) {
    epd_send_cmd(0x22);             // Display Update Control
    epd_send_data(0xC7);             // fast:0x0c, quality:0x0f, 0xcf
    epd_send_cmd(0x20);             // Activate Display Update Sequence
    epd_wait_busy();
}

void epd_turn_on_full() {
    epd_turn_on_with_mode(DISPLAY_TURN_ON_MODE_FULL);
}

void epd_turn_on_part() {
    epd_turn_on_with_mode(DISPLAY_TURN_ON_MODE_PART);
}

/****************************************************************************************************/
void epd_send(const uint8_t &dat, const int &dc_pin_value) {
    pin_write(EPD_DC_PIN, dc_pin_value);
    pin_write(EPD_CS_PIN, LOW);
    spi_write_byte(dat);
    pin_write(EPD_CS_PIN, HIGH);
}

void epd_send_cmd(const uint8_t &cmd) {
    epd_send(cmd, LOW);
}

void epd_send_data(const uint8_t &dat) {
    epd_send(dat, HIGH);
}