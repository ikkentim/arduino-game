#ifndef ARDUINOGAME_SHAPERENDERER_H
#define ARDUINOGAME_SHAPERENDERER_H

#include <inttypes.h>
#include <MI0283QT9.h>
#include "Color.h"

class ShapeRenderer {
public:
    void render(MI0283QT9 *tft, uint32_t *shape, Color color, float oldx, float oldy, float oldr, float newx,
                float newy, float newr);

private:
    void buffer_clear(uint32_t *buffer);

    void buffer_rotate(uint32_t *in, uint32_t *out, float rotation);

    void buffer_render(MI0283QT9 *tft, uint32_t *buffer, int x, int y, Color color);

    void buffer_from_pgm(uint32_t *buffer, uint16_t length, uint32_t *address);
    void buffer_copy(uint32_t *in, uint32_t *out);
    void buffer_xor_offset(uint32_t *old_buffer, uint32_t *new_buffer, int ox, int oy);
    uint32_t buffer1_[32];
    uint32_t buffer2_[32];
    uint32_t buffer3_[32];
};


#endif //ARDUINOGAME_SHAPERENDERER_H
