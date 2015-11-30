#ifndef ARDUINOGAME_SHAPERENDERER_H
#define ARDUINOGAME_SHAPERENDERER_H

#include <inttypes.h>
#include <TFT.h>
#include "Color.h"

#define SHAPE_SIZE  16
#define SHAPE_ORIGIN 8

typedef uint16_t ShapeBuffer;

class ShapeRenderer {
public:
    void render(TFT *tft, ShapeBuffer *shape, Color color, int oldx, int oldy, float oldr, int newx, int newy,
                float newr, bool force = false);

private:

    void buffer_rotate(ShapeBuffer *in, ShapeBuffer *out, float rotation);

    void buffer_render(TFT *tft, ShapeBuffer *buffer, int x, int y, Color color);

    void buffer_render_set(TFT *tft, ShapeBuffer *buffer, int x, int y, Color color);

    void buffer_diff_offset(ShapeBuffer *old_buffer, ShapeBuffer *new_buffer, int ox, int oy);

    void buffer_clear(ShapeBuffer *buffer);

    void buffer_from_pgm(ShapeBuffer *buffer, ShapeBuffer *address);

    void buffer_copy(ShapeBuffer *in, ShapeBuffer *out);

    ShapeBuffer buffer1_[SHAPE_SIZE];
    ShapeBuffer buffer2_[SHAPE_SIZE];
    ShapeBuffer buffer3_[SHAPE_SIZE];
};


#endif //ARDUINOGAME_SHAPERENDERER_H
