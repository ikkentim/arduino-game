#ifndef ARDUINOGAME_SHAPERENDERER_H
#define ARDUINOGAME_SHAPERENDERER_H

#include <inttypes.h>
#include <TFT.h>
#include "Color.h"

class ShapeRenderer {
public:
    void render(TFT *tft, int8_t *shape, int length, Color color, int oldx, int oldy, float oldr, int newx,
                int newy, float newr);
private:
    void buffer_draw_line(uint32_t *buffer, int startX, int startY, int endX, int endY);
    void buffer_set_pixel(uint32_t *buffer, int x, int y, uint8_t value);
    void buffer_clear(uint32_t *buffer);
    uint8_t buffer_get_pixel(uint32_t *buffer, int x, int y);
    uint32_t buffer1_[32];
};


#endif //ARDUINOGAME_SHAPERENDERER_H
