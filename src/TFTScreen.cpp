#include "TFTScreen.h"
# include <avr/io.h>
# include <avr/pgmspace.h>
# include <util/delay.h>

# include "TFTDef.h"
#include "fonts/fonts.h"

#define MIN_PRESSURE    5 //minimum pressure 1...254

#ifndef SWAP
#define SWAP(x, y) do{ (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }while(0)
#endif

TFTScreen::TFTScreen() :
    width(lcd_width),
    height(lcd_height) {

    DDRB |= _BV(PORTB5) | _BV(PORTB3) | _BV(PORTB2) | _BV(PORTB1) | _BV(PORTB0);
    DDRB &= ~_BV(PORTB4);
    DDRD |= _BV(PORTD7) | _BV(PORTD6);

    SPCR = _BV(SPE) | _BV(MSTR);

    PORTB &= ~_BV(PORTB0);// enable rst
    PORTB |= _BV(PORTB6) | _BV(PORTB2) | _BV(PORTB1);// enable led, disable adscs
    PORTD |= _BV(PORTD7);// disable cs

    reset();
}

void TFTScreen::set_area(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    transfer_command(LCD_CMD_COLUMN);
    transfer_word(x0);
    transfer_word(x1);
    transfer_command(LCD_CMD_PAGE);
    transfer_word(y0);
    transfer_word(y1);
}

void TFTScreen::draw_start() {
    transfer_command(LCD_CMD_WRITE);
    PORTD &= ~_BV(PORTD7);// enable cs
}

void TFTScreen::draw(Color color) {
    transfer(color >> 8, 1);
    transfer(color, 1);
}

void TFTScreen::draw_stop() {
    PORTD |= _BV(PORTD7);// disable cs
}

void TFTScreen::reset() {
    uint_least8_t c, i;
    const uint8_t *ptr;

    //reset
    PORTD |= _BV(PORTD7);// disable cs
    PORTB &= ~_BV(PORTB0);// enable rst
    _delay_ms(50);
    PORTB |= _BV(PORTB0);// disable rst
    _delay_ms(120);

    //send init commands and data
    ptr = &initdataQT9[0];
    while (1) {
        c = pgm_read_byte(ptr++);
        if (c == 0xFF) //end of data
        {
            break;
        }
        switch (c & 0xC0) {
            case 0x40: //command
                for (i = c & 0x3F; i != 0; i--) {
                    c = pgm_read_byte(ptr++);
                    transfer_command(c);
                }
                break;
            case 0x80: //data
                for (i = c & 0x3F; i != 0; i--) {
                    c = pgm_read_byte(ptr++);
                    transfer_byte(c);
                }
                break;
            case 0xC0: //delay
                c = c & 0x3F;
                for (; c > 0; c -= 10)
                    _delay_ms(10);
                break;
        }
    }
}

void TFTScreen::transfer_command(uint8_t cmd) {
    PORTD &= ~_BV(PORTD7);// enable cs
    transfer(cmd, 0);
    PORTD |= _BV(PORTD7);// disable cs
}

void TFTScreen::transfer_word(uint16_t data) {
    PORTD &= ~_BV(PORTD7);// enable cs
    transfer(data >> 8, 1);
    transfer(data, 1);
    PORTD |= _BV(PORTD7);// disable cs
}

void TFTScreen::transfer_byte(uint8_t data) {
    PORTD &= ~_BV(PORTD7);// enable cs
    transfer(data, 1);
    PORTD |= _BV(PORTD7);// disable cs
}

//uint8_t TFTScreen::transfer(uint8_t data, uint8_t high) {
//    if (high == 1)
//        PORTB |= _BV(PORTD3);// high mosi
//    else if (high == 0)
//        PORTB &= ~_BV(PORTD3);// low mosi
//
//    if (high != 2) {
//        PORTB &= ~_BV(PORTB5);// low sck
//        SPCR &= ~(1 << SPE);
//        PORTB |= _BV(PORTB5);// high sck
//        SPCR |= (1 << SPE);
//    }
//
//    SPDR = data;
//    while (!(SPSR & (1 << SPIF)));
//
//    return SPDR;
//}

void TFTScreen::fill_screen(Color color) {
    set_area(0, 0, width - 1, height - 1);
    draw_start();
    for (uint32_t size = (((uint32_t) width * height)); size != 0; size--) {
        draw(color);
    }
    draw_stop();

    return;
}

void TFTScreen::draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Color color) {
    int_least16_t dx, dy, dx2, dy2, err, stepx, stepy;

    if (x0 == x1) //horizontal line
    {
        if (x0 < 0 || x0 >= width || (y0 < 0 && y1 < 0) || (y0 >= height && y1 >= height)) return;
        if (y0 > y1) { SWAP(y1, y0); }
        if (y0 < 0) y0 = 0;
        if (y1 >= height) y1 = height - 1;

        fill_rectangle(x0, y0, 1, y1 - y0 + 1, color);
    }
    else if (y0 == y1) //vertical line
    {
        if (y0 < 0 || y0 >= height || (x0 < 0 && x1 < 0) || (x0 >= width && x1 >= width)) return;
        if (x0 > x1) { SWAP(x1, x0); }
        if (x0 < 0) x0 = 0;
        if (x1 >= width) x1 = width - 1;

        fill_rectangle(x0, y0, x1 - x0 + 1, 1, color);
    }
    else {
        //calculate direction
        dx = x1 - x0;
        dy = y1 - y0;
        if (dx < 0) {
            dx = -dx;
            stepx = -1;
        } else { stepx = +1; }
        if (dy < 0) {
            dy = -dy;
            stepy = -1;
        } else { stepy = +1; }
        dx2 = dx << 1;
        dy2 = dy << 1;
        //draw line
        draw_pixel(x0, y0, color);
        if (dx > dy) {
            err = dy2 - dx;
            while (x0 != x1) {
                if (err >= 0) {
                    y0 += stepy;
                    err -= dx2;
                }
                x0 += stepx;
                err += dy2;
                draw_pixel(x0, y0, color);
            }
        }
        else {
            err = dx2 - dy;
            while (y0 != y1) {
                if (err >= 0) {
                    x0 += stepx;
                    err -= dy2;
                }
                y0 += stepy;
                err += dx2;
                draw_pixel(x0, y0, color);
            }
        }
    }
}

void TFTScreen::draw_pixel(int16_t x, int16_t y, Color color) {
    if (x >= width || y >= height || x < 0 || y < 0)
        return;

    set_area(x, y, x, y);

    draw_start();
    draw(color);
    draw_stop();

    asm("");
}

void TFTScreen::fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h, Color color) {

    if (x + w < 0 || y + h < 0 || x >= width || y >= width)
        return;

    if (x + w >= width) w = width - x;
    if (y + h >= height) h = height - y;

    set_area(x, y, x + w - 1, y + h - 1);

    draw_start();

    for (uint32_t size = ((uint32_t) w * h); size != 0; size--)
        draw(color);

    draw_stop();

    return;
}

int16_t TFTScreen::draw_text(int16_t x, int16_t y, const char *s, Color color, Color bg, uint8_t size) {
    while (*s != 0) {
        x = draw_char(x, y, *s++, color, bg, size);
        if (x >= width) break;
    }

    return x;
}

int16_t TFTScreen::draw_text_pgm(int16_t x, int16_t y, PGM_P s, Color color, Color bg, uint8_t size) {
    char c = (char) pgm_read_byte(s++);
    while (c != 0) {
        x = draw_char(x, y, c, color, bg, size);
        if (x > lcd_width) break;
        c = (char) pgm_read_byte(s++);
    }

    return x;
}


int16_t TFTScreen::draw_char(int16_t x, int16_t y, char c, Color color, Color bg, uint8_t size) {

    if(c > 0x2f) c -= 15;
    int16_t
        ret,
        pos = (c - FONT_START) * (8 * FONT_HEIGHT / 8);

    uint8_t
        data, mask,
        i, j,
        w = FONT_WIDTH,
        h = FONT_HEIGHT;

    const PROGMEM uint8_t *ptr = &font_PGM[pos];

    size = size & 0x7F;

    if (size <= 1) {
        ret = x + w;
        if ((ret - 1) >= width)
            return width + 1;
        else if ((y + h - 1) >= height)
            return width + 1;

        set_area(x, y, (x + w - 1), (y + h - 1));

        draw_start();
        for (; h != 0; h--) {
            data = pgm_read_byte(ptr);
            ptr += 1;
            for (mask = ((uint8_t) 1 << (w - 1)); mask != 0; mask >>= 1) {
                if (data & mask)
                    draw(color);
                else
                    draw(bg);
            }
        }
        draw_stop();
    }
    else {
        ret = x + (w * size);
        if ((ret - 1) >= width)
            return width + 1;
        else if ((y + (h * size) - 1) >= height)
            return width + 1;

        set_area(x, y, (x + (w * size) - 1), (y + (h * size) - 1));

        draw_start();
        for (; h != 0; h--) {
            data = pgm_read_byte(ptr);
            ptr += 1;
            for (i = size; i != 0; i--)
                for (mask = ((uint8_t) 1 << (w - 1)); mask != 0; mask >>= 1) {
                    if (data & mask) {
                        for (j = size; j != 0; j--)
                            draw(color);
                    }
                    else {
                        for (j = size; j != 0; j--)
                            draw(bg);
                    }
                }
        }
        draw_stop();
    }

    return ret;
}

uint8_t TFTScreen::touch_read() {
    uint_least8_t p, a, b;

    //get pressure
    PORTB &= ~_BV(PORTD6);// enable adscs
    transfer(ADS_CMD_START | ADS_CMD_8BIT | ADS_CMD_DIFF | ADS_CMD_Z1_POS, 2);
    a = transfer(0x00, 2) & 0x7F;
    transfer(ADS_CMD_START | ADS_CMD_8BIT | ADS_CMD_DIFF | ADS_CMD_Z2_POS, 2);
    b = (255 - transfer(0x00, 2)) & 0x7F;
    PORTB |= _BV(PORTD6);// disable adscs
    p = a + b;

    return (uint8_t)(p > MIN_PRESSURE);
}


void TFTScreen::draw_circle(int16_t x, int16_t y, int16_t radius, Color color) {
    int16_t err, xx, yy;

    err = -radius;
    xx = radius;
    yy = 0;

    while (xx >= yy) {
        draw_pixel(x + xx, y + yy, color);
        draw_pixel(x - xx, y + yy, color);
        draw_pixel(x + xx, y - yy, color);
        draw_pixel(x - xx, y - yy, color);
        draw_pixel(x + yy, y + xx, color);
        draw_pixel(x - yy, y + xx, color);
        draw_pixel(x + yy, y - xx, color);
        draw_pixel(x - yy, y - xx, color);

        err += yy++;
        err += yy;
        if (err >= 0) {
            xx--;
            err = err - xx - xx;
        }
    }
}

void TFTScreen::fill_circle(int16_t x, int16_t y, int16_t radius, Color color) {
    int16_t err, xx, yy;

    err = -radius;
    xx = radius;
    yy = 0;

    while (xx >= yy) {
        draw_line(x - xx, y + yy, x + xx, y + yy, color);
        draw_line(x - xx, y - yy, x + xx, y - yy, color);
        draw_line(x - yy, y + xx, x + yy, y + xx, color);
        draw_line(x - yy, y - xx, x + yy, y - xx, color);

        err += yy++;
        err += yy;
        if (err >= 0) {
            xx--;
            err = err - xx - xx;
        }
    }
}