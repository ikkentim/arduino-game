#include "ShapeRenderer.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "FastMath.h"

void ShapeRenderer::render(MI0283QT9 *tft, uint32_t *shape, Color color, float oldx, float oldy, float oldr, float newx,
                           float newy, float newr) {
    buffer_clear(buffer1_);
    buffer_clear(buffer2_);
    buffer_clear(buffer3_);

    buffer_from_pgm(buffer1_, 32, shape);

    buffer_rotate(buffer1_, buffer2_, oldr);
    buffer_rotate(buffer1_, buffer3_, newr);

    buffer_copy(buffer2_, buffer1_);
    //buffer_xor_offset(buffer2_, buffer3_, (int) oldx - (int) newx, (int) oldy - (int) newy);
    //buffer_xor_offset(buffer3_, buffer1_, (int) newx - (int) oldx, (int) newx - (int) oldy);

    buffer_render(tft, buffer2_, (int) oldx, (int) oldy, 0);
    buffer_render(tft, buffer3_, (int) newx, (int) newy, color);
}

void ShapeRenderer::buffer_clear(uint32_t *buffer) {
    for (uint8_t i = 0; i < 32; i++) {
        buffer[i] = 0;
    }
}

void ShapeRenderer::buffer_rotate(uint32_t *in, uint32_t *out, float rotation) {
    float s = fast_sin(rotation);
    float c = fast_cos(rotation);

    for (uint8_t y = 0; y < 32; y++)
        for (uint8_t x = 0; x < 32; x++) {
            if(!((in[y] >> x) & 1) ) continue;

            int nx = (int) (c * (x-16) - s * (y-16) + 16);
            int ny = (int) (s * (x-16) + c * (y-16) + 16);

            out[ny] |= ((in[y] >> x) & 1) << nx;
        }
}

void ShapeRenderer::buffer_render(MI0283QT9 *tft, uint32_t *buffer, int x, int y, Color color) {
    for (uint8_t cy = 0; cy < 32; cy++)
        for (uint8_t cx = 0; cx < 32; cx++) {
            if ((buffer[cy] >> (31 - cx)) & 1) {
                tft->drawPixel(x + cx, y + cy, color);
            }
        }
}

void ShapeRenderer::buffer_from_pgm(uint32_t *buffer, uint16_t length, uint32_t *address) {
    for (uint16_t i = 0; i < length; i++)
        buffer[i] = pgm_read_dword(address + i);
}

void ShapeRenderer::buffer_xor_offset(uint32_t *buffer1, uint32_t *buffer2, int ox, int oy) {
    for (uint8_t y = 0; y < 32; y++) {
        for (uint8_t x = 0; x < 32; x++) {
            uint32_t bit1 = (buffer1[y] >> (31 - x)) & 1;

            int x2 = x + ox;
            int y2 = y + oy;
            uint8_t bit2 = x2 < 0 || x2 >= 32 || y2 < 0 || y2 >= 32
                       ? 0
                       : (buffer2[y2] >> (31 - x2)) & 1;

            uint32_t bit = (uint32_t)1 << (31 - x);
            uint8_t value = (bit1 & ~bit2) & 1;
            if((buffer1[y] & bit) && !value)
                buffer1[y] &= ~bit;
            else if(!(buffer1[y] & bit) && value)
                buffer1[y] |= bit;
        }
    }
}

void ShapeRenderer::buffer_copy(uint32_t *in, uint32_t *out) {
    for (uint8_t i=0; i < 32; i++)
        out[i] = in[i];
}
