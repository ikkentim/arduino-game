#ifndef ARDUINOGAME_TFT_H
#define ARDUINOGAME_TFT_H

#include <inttypes.h>
#include "Color.h"

typedef struct {
    uint32_t x;
    uint32_t y;
} CAL_POINT;

typedef struct
{
    uint_least32_t a;
    uint_least32_t b;
    uint_least32_t c;
    uint_least32_t d;
    uint_least32_t e;
    uint_least32_t f;
    uint_least32_t div;
} CAL_MATRIX;

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
    void touch_calibrate();
    int16_t touch_x();
    int16_t touch_y();
    int16_t touch_z();

    uint16_t width;
    uint16_t height;

private:
    void reset();
    void transfer_command(uint8_t cmd);
    void transfer_word(uint16_t data);
    void transfer_byte(uint8_t data);
    uint8_t transfer(uint8_t data, uint8_t high);

    void touch_calculate();
    void touch_set_cal(CAL_POINT *lcd, CAL_POINT *tp);

    int_least16_t lcd_x, lcd_y, lcd_z;   //calibrated pos (screen)
    int_least16_t tp_x, tp_y;            //raw pos (touch panel)
    int_least16_t tp_last_x, tp_last_y;  //last raw pos (touch panel)
    CAL_MATRIX tp_matrix;                //calibration matrix
};

#endif //ARDUINOGAME_TFT_H