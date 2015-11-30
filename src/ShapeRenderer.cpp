#include "ShapeRenderer.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "FastMath.h"
#include <math.h>

#define ROTATION_STEP_SIZE  0.1f

#define IN_RANGE(value, min, max) (value >= min && value < max) //inclusive min, exclusive max

void ShapeRenderer::render(TFT *tft, ShapeBuffer *shape, Color color, int oldx, int oldy, float oldr, int newx,
                           int newy, float newr, bool force) {
    // snap rotations to step size.
    float tmp = 0;
    if (oldr > 0) {
        while (tmp < oldr) tmp += ROTATION_STEP_SIZE;
        oldr = tmp;
    }
    else {
        while (tmp > oldr) tmp -= ROTATION_STEP_SIZE;
        oldr = tmp;
    }
    tmp = 0;
    if (newr > 0) {
        while (tmp < newr) tmp += ROTATION_STEP_SIZE;
        newr = tmp;
    }
    else {
        while (tmp > newr) tmp -= ROTATION_STEP_SIZE;
        newr = tmp;
    }

    // check if anything has changed.
    if (!force && oldx == newx && oldy == newy && oldr == newr)
        return;

    // clear both buffer 2 and 3.
    for (uint8_t i = 0; i < SHAPE_SIZE; i++) {
        buffer2_[i] = 0;
        buffer3_[i] = 0;
    }

    // fill buffer 1 from pgm.
    buffer_from_pgm(buffer1_, shape);

    // rotate buffer 2 like previous render. rotate buffer 3 like current render.
    buffer_rotate(buffer1_, buffer2_, oldr);
    buffer_rotate(buffer1_, buffer3_, newr);

    //buffer_copy(buffer2_, buffer1_);
    buffer_diff_offset(buffer2_, buffer3_, oldx - newx, oldy - newy);
    //buffer_diff_offset(buffer3_, buffer1_, newx - oldx, newx - oldy);

    buffer_render_set(tft, buffer2_, oldx, oldy, 0);
    //buffer_render_set(tft, buffer3_, newx, newy, color);
    buffer_render(tft, buffer3_, newx, newy, color);

    //buffer_render_set(tft, buffer3_, newx, newy, RGB(255,0,0));
}

void ShapeRenderer::buffer_rotate(ShapeBuffer *in, ShapeBuffer *out, float rotation) {
    float s = fast_sin(rotation);
    float c = fast_cos(rotation);

    for (uint8_t y = SHAPE_SIZE - 1; y != 0; y--)
        for (uint8_t x = SHAPE_SIZE - 1; x != 0; x--) {
            if (!((in[y] >> x) & 1)) continue;

            int nx = (int) (c * (x - SHAPE_ORIGIN) - s * (y - SHAPE_ORIGIN) + SHAPE_ORIGIN);
            int ny = (int) (s * (x - SHAPE_ORIGIN) + c * (y - SHAPE_ORIGIN) + SHAPE_ORIGIN);

            if (IN_RANGE(nx, 0, SHAPE_SIZE) && IN_RANGE(ny, 0, SHAPE_SIZE))
                out[ny] |= ((in[y] >> x) & 1) << nx;
        }
}

void ShapeRenderer::buffer_render_set(TFT *tft, ShapeBuffer *buffer, int x, int y, Color color) {
    for (uint8_t cx = SHAPE_SIZE - 1; cx != 0; cx--) {
        ShapeBuffer mask = (ShapeBuffer) 1 << (SHAPE_SIZE - 1 - cx);
        for (uint8_t cy = SHAPE_SIZE - 1; cy != 0; cy--)
            if ((buffer[cy] & mask))
                tft->drawPixel(x + cx, y + cy, color);
    }
}

void ShapeRenderer::buffer_render(TFT *tft, ShapeBuffer *buffer, int x, int y, Color color) {
    // set area to be drawn
    tft->setArea(x, y, x + SHAPE_SIZE - 1, y + SHAPE_SIZE - 1);
    tft->drawStart();

    for (uint8_t cy = 0; cy < SHAPE_SIZE; cy++)
    for (uint8_t cx = 0; cx < SHAPE_SIZE; cx++) {
        ShapeBuffer mask = (ShapeBuffer) 1 << (SHAPE_SIZE - 1 - cx);
            tft->draw((buffer[cy] & mask) ? color : 0);
    }
    tft->drawStop();
}

void ShapeRenderer::buffer_diff_offset(ShapeBuffer *buffer1, ShapeBuffer *buffer2, int ox, int oy) {
    for (uint8_t y = SHAPE_SIZE - 1; y != 0; y--)
        for (uint8_t x = SHAPE_SIZE - 1; x != 0; x--) {
            // calculate positions within buffer 2.
            int x2 = x + ox;
            int y2 = y + oy;

            // create mask for bit in buffers.
            ShapeBuffer mask1 = (ShapeBuffer) 1 << (SHAPE_SIZE - 1 - x);
            ShapeBuffer mask2 = (ShapeBuffer) 1 << (SHAPE_SIZE - 1 - x2);

            // calculate diff value based on the set bits in buffer 1 and 2.
            uint8_t value =
                // (bit representing current position in buffer 1) &
                (buffer1[y] & mask1 ? 1 : 0) &
                ~(
                    IN_RANGE(x2, 0, SHAPE_SIZE) && IN_RANGE(y2, 0, SHAPE_SIZE)
                    ? ((buffer2[y2] & mask2) ? (uint8_t) 1 : 0)
                    : 0
                );

            // set diff value.
            if (((buffer1[y] & mask1) == 0) != (value == 0))
                buffer1[y] ^= mask1;
        }
}

void ShapeRenderer::buffer_from_pgm(ShapeBuffer *buffer, ShapeBuffer *address) {
    for (uint8_t i = 0; i < SHAPE_SIZE; i++)
        buffer[i] = pgm_read_word(address + i);
}

void ShapeRenderer::buffer_copy(ShapeBuffer *in, ShapeBuffer *out) {
    memcpy(out, in, sizeof(ShapeBuffer) * SHAPE_SIZE);
}

void ShapeRenderer::buffer_clear(ShapeBuffer *buffer) {
    memset(buffer, 0, sizeof(ShapeBuffer) * SHAPE_SIZE);
}
