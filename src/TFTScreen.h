#ifndef ARDUINOGAME_TFT_H
#define ARDUINOGAME_TFT_H

#include <avr/io.h>
#include <inttypes.h>
#include "Color.h"

class TFTScreen
{
public:
    TFTScreen();
    void set_area(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void draw_start();
    void draw_stop();
    void draw(Color color);

    void fill_screen(Color color);
    void draw_pixel(int16_t x, int16_t y, Color color);
    void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Color color);
    void fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h, Color color);
    int16_t draw_text(int16_t x, int16_t y, const char *s, Color color, Color bg, uint8_t size);
    int16_t draw_text_pgm(int16_t x, int16_t y, const char *s, Color color, Color bg, uint8_t size);
    int16_t draw_char(int16_t x, int16_t y, char c, Color color, Color bg, uint8_t size);
    void draw_circle(int16_t x, int16_t y, int16_t r, Color color);
    void fill_circle(int16_t x, int16_t y, int16_t r, Color color);

    uint8_t touch_read();

    uint16_t width;
    uint16_t height;

private:
    void reset();
    void transfer_command(uint8_t cmd);
    inline void transfer_word(uint16_t data);
    inline void transfer_byte(uint8_t data);
    inline uint8_t transfer(uint8_t data, uint8_t high) {
        if (high == 1)
            PORTB |= _BV(PORTD3);// high mosi
        else if (high == 0)
            PORTB &= ~_BV(PORTD3);// low mosi

        if (high != 2) {
            PORTB &= ~_BV(PORTB5);// low sck
            SPCR &= ~(1 << SPE);
            PORTB |= _BV(PORTB5);// high sck
            SPCR |= (1 << SPE);
        }

        SPDR = data;
        while (!(SPSR & (1 << SPIF)));

        return SPDR;
    }
};

#endif //ARDUINOGAME_TFT_H