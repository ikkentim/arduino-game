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

    PORTB |= _BV(PORTB2);

    SPCR = _BV(SPE) | _BV(MSTR);

    RST_ENABLE();
    LED_ENABLE();
    CS_DISABLE();

    ADSCS_DISABLE();
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
    CS_ENABLE();
}

void TFTScreen::draw(Color color) {
    transfer(color >> 8, 1);
    transfer(color, 1);
}

void TFTScreen::draw_stop() {
    CS_DISABLE();
}

void TFTScreen::reset() {
    uint_least8_t c, i;
    const uint8_t *ptr;

    //reset
    CS_DISABLE();
    RST_ENABLE();
    _delay_ms(50);
    RST_DISABLE();
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
    CS_ENABLE();
    transfer(cmd, 0);
    CS_DISABLE();
}

void TFTScreen::transfer_word(uint16_t data) {
    CS_ENABLE();
    transfer(data >> 8, 1);
    transfer(data, 1);
    CS_DISABLE();
}

void TFTScreen::transfer_byte(uint8_t data) {
    CS_ENABLE();
    transfer(data, 1);
    CS_DISABLE();
}

uint8_t TFTScreen::transfer(uint8_t data, uint8_t high) {
    if (high == 1)
        MOSI_HIGH();
    else if (high == 0)
        MOSI_LOW();

    if (high != 2) {
        SCK_LOW();
        SPCR &= ~(1 << SPE);
        SCK_HIGH();
        SPCR |= (1 << SPE);
    }

    SPDR = data;
    while (!(SPSR & (1 << SPIF)));

    return SPDR;
}

void TFTScreen::fill_screen(Color color) {
    set_area(0, 0, width - 1, height - 1);
    draw_start();
    for (uint32_t size = (((uint32_t) width * height) / 8U); size != 0; size--) {
        draw(color);
        draw(color);
        draw(color);
        draw(color);
        draw(color);
        draw(color);
        draw(color);
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

uint_least8_t TFTScreen::touch_read() {
    uint_least8_t p, a1, a2, b1, b2;
    uint_least16_t x, y;


    //get pressure
    ADSCS_ENABLE();
    transfer(ADS_CMD_START | ADS_CMD_8BIT | ADS_CMD_DIFF | ADS_CMD_Z1_POS, 2);
    a1 = transfer(0x00, 2) & 0x7F;
    transfer(ADS_CMD_START | ADS_CMD_8BIT | ADS_CMD_DIFF | ADS_CMD_Z2_POS, 2);
    b1 = (255 - transfer(0x00, 2)) & 0x7F;
    ADSCS_DISABLE();
    p = a1 + b1;

    if (p > MIN_PRESSURE) {
        //using 2 samples for x and y position
        ADSCS_ENABLE();
        //get X data
        transfer(ADS_CMD_START | ADS_CMD_12BIT | ADS_CMD_DIFF | ADS_CMD_X_POS, 2);
        a1 = transfer(0x00, 2);
        b1 = transfer(0x00, 2);
        transfer(ADS_CMD_START | ADS_CMD_12BIT | ADS_CMD_DIFF | ADS_CMD_X_POS, 2);
        a2 = transfer(0x00, 2);
        b2 = transfer(0x00, 2);

        if (a1 == a2) {
            x = 1023 - ((a2 << 2) | (b2 >> 6));

            //get Y data
            transfer(ADS_CMD_START | ADS_CMD_12BIT | ADS_CMD_DIFF | ADS_CMD_Y_POS, 2);
            a1 = transfer(0x00, 2);
            b1 = transfer(0x00, 2);
            transfer(ADS_CMD_START | ADS_CMD_12BIT | ADS_CMD_DIFF | ADS_CMD_Y_POS, 2);
            a2 = transfer(0x00, 2);
            b2 = transfer(0x00, 2);

            if (a1 == a2) {
                y = ((a2 << 2) | (b2 >> 6));
                if (x && y) {
                    tp_x = x;
                    tp_y = y;
                }
                lcd_z = p;
            }
        }
        ADSCS_DISABLE();
    }
    else {
        lcd_z = 0;
    }

    if (lcd_z != 0) {
        return 1;
    }
    return 0;
}


void TFTScreen::touch_calibrate() {
    uint8_t i;
    CAL_POINT lcd_points[3] = {CAL_POINT1, CAL_POINT2, CAL_POINT3}; //calibration point postions
    CAL_POINT tp_points[3];
    uint16_t o;

    //clear screen
    fill_screen(RGB(255, 255, 255));

    draw_text_pgm((lcd_width / 2) - 50, (lcd_height / 2) - 10, PSTR("Calibration"), RGB(0, 0, 0), RGB(255, 255, 255),
                  1);
    while (touch_read()); //wait for touch release

    //show calibration points
    for (i = 0; i < 3;) {
        //draw points
        draw_circle(lcd_points[i].x, lcd_points[i].y, 2, RGB(0, 0, 0));
        draw_circle(lcd_points[i].x, lcd_points[i].y, 5, RGB(0, 0, 0));
        draw_circle(lcd_points[i].x, lcd_points[i].y, 10, RGB(255, 0, 0));

        //press dectected? -> save point
        if (touch_read()) {
            fill_circle(lcd_points[i].x, lcd_points[i].y, 2, RGB(255, 0, 0));
            tp_points[i].x = (uint32_t) tp_x;
            tp_points[i].y = (uint32_t) tp_y;
            i++;

            //wait and redraw screen
            _delay_ms(100);
            fill_screen(RGB(255, 255, 255));
            if (i < 3) {
                draw_text_pgm((lcd_width / 2) - 50, (lcd_height / 2) - 10, PSTR("Calibration"), RGB(0, 0, 0),
                              RGB(255, 255, 255), 1);
            }
        }
    }

    //calulate calibration matrix
    touch_set_cal(lcd_points, tp_points);

    //wait for touch release
    while (touch_read()); //wait for touch release

    return;
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

void TFTScreen::touch_set_cal(CAL_POINT *lcd, CAL_POINT *tp) {
    tp_matrix.div = ((tp[0].x - tp[2].x) * (tp[1].y - tp[2].y)) -
                    ((tp[1].x - tp[2].x) * (tp[0].y - tp[2].y));

    if (tp_matrix.div == 0)
        return;

    tp_matrix.a = ((lcd[0].x - lcd[2].x) * (tp[1].y - tp[2].y)) -
                  ((lcd[1].x - lcd[2].x) * (tp[0].y - tp[2].y));

    tp_matrix.b = ((tp[0].x - tp[2].x) * (lcd[1].x - lcd[2].x)) -
                  ((lcd[0].x - lcd[2].x) * (tp[1].x - tp[2].x));

    tp_matrix.c = (tp[2].x * lcd[1].x - tp[1].x * lcd[2].x) * tp[0].y +
                  (tp[0].x * lcd[2].x - tp[2].x * lcd[0].x) * tp[1].y +
                  (tp[1].x * lcd[0].x - tp[0].x * lcd[1].x) * tp[2].y;

    tp_matrix.d = ((lcd[0].y - lcd[2].y) * (tp[1].y - tp[2].y)) -
                  ((lcd[1].y - lcd[2].y) * (tp[0].y - tp[2].y));

    tp_matrix.e = ((tp[0].x - tp[2].x) * (lcd[1].y - lcd[2].y)) -
                  ((lcd[0].y - lcd[2].y) * (tp[1].x - tp[2].x));

    tp_matrix.f = (tp[2].x * lcd[1].y - tp[1].x * lcd[2].y) * tp[0].y +
                  (tp[0].x * lcd[2].y - tp[2].x * lcd[0].y) * tp[1].y +
                  (tp[1].x * lcd[0].y - tp[0].x * lcd[1].y) * tp[2].y;
}

void TFTScreen::touch_calculate() {
    uint32_t x, y;

    //calc x pos
    if (tp_x != tp_last_x) {
        tp_last_x = tp_x;
        x = (uint32_t) tp_x;
        y = (uint32_t) tp_y;
        x = ((tp_matrix.a * x) + (tp_matrix.b * y) + tp_matrix.c) / tp_matrix.div;

        if (x >= (width * 2)) x = 0;
        else if (x >= (width * 1)) x = width - 1;

        lcd_x = x;
    }

    //calc y pos
    if (tp_y != tp_last_y) {
        tp_last_y = tp_y;
        x = (uint32_t) tp_x;
        y = (uint32_t) tp_y;
        y = ((tp_matrix.d * x) + (tp_matrix.e * y) + tp_matrix.f) / tp_matrix.div;

        if (y >= (height * 2)) y = 0;
        else if (y >= (height * 1)) y = height - 1;

        lcd_y = y;
    }
}

int16_t TFTScreen::touch_x() {
    touch_calculate();
    return lcd_x;
}


int16_t TFTScreen::touch_y() {
    touch_calculate();
    return lcd_y;
}


int16_t TFTScreen::touch_z() {
    return lcd_z;
}