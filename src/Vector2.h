#ifndef ARDUINO_GAME_VECTOR2_H
#define ARDUINO_GAME_VECTOR2_H

#include <math.h>

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0), y(0) {

    }

    Vector2(float xx, float yy) : x(xx), y(yy) {

    }

    inline void zero() {
        x = 0;
        y = 0;
    }

    inline bool is_zero() const {
        return x == 0 && y == 0;
    }

    inline float length() {
        return (float)sqrt(length_sq());
    }

    inline float length_sq() {
        return x * x + y * y;
    }

    inline void normalize() {
        float len = length();
        x /= len;
        y /= len;
    }

    inline Vector2 normalized() {
        Vector2 r = *this;
        r.normalize();
        return r;
    }

    inline float dot(const Vector2 &v2) const {
        return x*v2.x + y*v2.y;
    }

    inline float cross(const Vector2 &v2) const {
        return x * v2.y - v2.x * y;
    }

    inline Vector2 operator=(Vector2 a) {
        x = a.x;
        y = a.y;
        return a;
    }

    inline Vector2 operator+(Vector2 a) {
        return Vector2(x + a.x, y + a.y);
    }

    inline Vector2 operator-(Vector2 a) {
        return Vector2(x - a.x, y - a.y);
    }

    inline Vector2 operator/(float scalar) {
        return Vector2(x / scalar, y / scalar);
    }

    inline bool operator==(Vector2 a) {
        return a.x == x && a.y == y;
    }

    inline bool operator!=(Vector2 a) {
        return a.x != x || a.y != y;
    }
};

#endif //ARDUINO_GAME_VECTOR2_H
