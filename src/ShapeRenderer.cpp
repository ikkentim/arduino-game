#include "ShapeRenderer.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "FastMath.h"
#include <math.h>

#define IN_RANGE(value, min, max) (value >= min && value < max) //inclusive min, exclusive max
#define SWAP(x, y) do{ (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }while(0)


void ShapeRenderer::render(MI0283QT9 *tft, int8_t *shape, int length, Color color, int oldx, int oldy, float oldr,
                           int newx, int newy, float newr) {
    float
        s = fast_sin(newr),
        c = fast_cos(newr);

    for (int i = 31; i != 0; i--)
        buffer1_[i] = 0;
    for (int j = 0, i = 0; i < length; i++) {
        int8_t
            x1 = (int8_t) pgm_read_byte(shape + j++),
            y1 = (int8_t) pgm_read_byte(shape + j++),
            x2 = (int8_t) pgm_read_byte(shape + j++),
            y2 = (int8_t) pgm_read_byte(shape + j++);

        int x3 = (int) (c * x1 - s * y1),
            y3 = (int) (s * x1 + c * y1),
            x4 = (int) (c * x2 - s * y2),
            y4 = (int) (s * x2 + c * y2);

        buffer_draw_line(buffer1_, x3 + 16, y3 + 16, x4 + 16, y4 + 16);
        tft->drawLine(x3 + newx, y3 + newy, x4 + newx, y4 + newy, color);
    }

    s = fast_sin(oldr);
    c = fast_cos(oldr);

    for (int j = 0, i = 0; i < length; i++) {
        int8_t
            x1 = (int8_t) pgm_read_byte(shape + j++),
            y1 = (int8_t) pgm_read_byte(shape + j++),
            x2 = (int8_t) pgm_read_byte(shape + j++),
            y2 = (int8_t) pgm_read_byte(shape + j++);

        int x3 = (int) (c * x1 - s * y1),
            y3 = (int) (s * x1 + c * y1),
            x4 = (int) (c * x2 - s * y2),
            y4 = (int) (s * x2 + c * y2);

        int_least16_t dx, dy, dx2, dy2, err, stepx, stepy;
        if (x3 == x4) //horizontal line
        {
            if (y3 > y4) { SWAP(y4, y3); }
            for (int y = y3; y <= y4; y++) {
                if (!buffer_get_pixel(buffer1_, x3 + (oldx - newx) + 16, y + (oldy - newy) + 16))
                    tft->drawPixel(x3 + oldx, y + oldy, 0);
            }
        }
        else if (y3 == y4) //vertical line
        {
            if (x3 > x4) { SWAP(x4, x3); }
            for (int x = x3; x <= x4; x++) {
                if (!buffer_get_pixel(buffer1_, x + (oldx - newx) + 16, y3 + (oldy - newy) + 16))
                    tft->drawPixel(x + oldx, y3 + oldy, 0);
            }
        }
        else {
            dx = x4 - x3;
            dy = y4 - y3;
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
            {
                if (!buffer_get_pixel(buffer1_, x3 + (oldx - newx) + 16, y3 + (oldy - newy) + 16))
                    tft->drawPixel(x3 + oldx, y3 + oldy, 0);
            }
            if (dx > dy) {
                err = dy2 - dx;
                while (x3 != x4) {
                    if (err >= 0) {
                        y3 += stepy;
                        err -= dx2;
                    }
                    x3 += stepx;
                    err += dy2;
                    if (!buffer_get_pixel(buffer1_, x3 + (oldx - newx) + 16, y3 + (oldy - newy) + 16))
                        tft->drawPixel(x3 + oldx, y3 + oldy, 0);
                }
            }
            else {
                err = dx2 - dy;
                while (y3 != y4) {
                    if (err >= 0) {
                        x3 += stepx;
                        err -= dy2;
                    }
                    y3 += stepy;
                    err += dx2;

                    if (!buffer_get_pixel(buffer1_, x3 + (oldx - newx) + 16, y3 + (oldy - newy) + 16))
                        tft->drawPixel(x3 + oldx, y3 + oldy, 0);
                }
            }
        }
    }
}

void ShapeRenderer::buffer_draw_line(uint32_t *buffer, int x0, int y0, int x1, int y1) {
    int_least16_t dx, dy, dx2, dy2, err, stepx, stepy;

    if (x0 == x1)
    {
        if (y0 > y1) { SWAP(y1, y0); }
        for (int y = y0; y <= y1; y++)
            buffer_set_pixel(buffer, x0, y, 1);
    }
    else if (y0 == y1)
    {
        if (x0 > x1) { SWAP(x1, x0); }
        for (int x = x0; x <= x1; x++)
            buffer_set_pixel(buffer, x, y0, 1);
    }
    else {
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
        buffer_set_pixel(buffer, x0, y0, 1);
        if (dx > dy) {
            err = dy2 - dx;
            while (x0 != x1) {
                if (err >= 0) {
                    y0 += stepy;
                    err -= dx2;
                }
                x0 += stepx;
                err += dy2;
                buffer_set_pixel(buffer, x0, y0, 1);
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
                buffer_set_pixel(buffer, x0, y0, 1);
            }
        }
    }

    return;
}

void ShapeRenderer::buffer_set_pixel(uint32_t *buffer, int x, int y, uint8_t value) {
    if (!value || !IN_RANGE(x, 0, 32) || !IN_RANGE(y, 0, 32)) return;
    buffer[y] |= ((uint32_t)1 << x);
}

uint8_t ShapeRenderer::buffer_get_pixel(uint32_t *buffer, int x, int y) {
    if (!IN_RANGE(x, 0, 32) || !IN_RANGE(y, 0, 32)) return 0;
    return buffer[y] & ((uint32_t)1 << x) ? 1 : 0;
}