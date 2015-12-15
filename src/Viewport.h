#ifndef ARDUINOGAME_VIEWPORT_H
#define ARDUINOGAME_VIEWPORT_H

#include "Vector2.h"
struct Viewport {
    int x;
    int y;
    int width;
    int height;

    Viewport(int a, int b, int w, int h) : x(a), y(b), width(w), height(h) {

    }

    Vector2 position() {
        return Vector2((float) x, (float) y);
    }

    Vector2 size() {
        return Vector2((float) width, (float) height);
    }

    bool is_in_range(Vector2 position, float range) {
        return (position.x > x - range) &&
               (position.x < x + width + range) &&
               (position.y > y - range) &&
               (position.y < y + height + range);
    }
};

#endif // ARDUINOGAME_VIEWPORT_H