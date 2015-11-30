#ifndef ARDUINOGAME_VECTOR2_H
#define ARDUINOGAME_VECTOR2_H

#include <math.h>
#include "Matrix4.h"

struct Vector2 {
    float x;
    float y;

    Vector2();
    Vector2(float xx, float yy);
    void zero();
    bool is_zero() const;
    float length();
    float length_sq();
    void normalize();
    Vector2 normalized();
    float dot(const Vector2 &v2) const;
    float cross(const Vector2 &v2) const;
    Vector2 transform(const struct Matrix4 &m) const;
    Vector2 operator=(Vector2 a);
    Vector2 operator+(Vector2 a);
    Vector2 operator-(Vector2 a);
    Vector2 operator/(float scalar);
    Vector2 operator*(float multiplier);
    bool operator==(Vector2 a);
    Vector2 operator+=(Vector2 a);
    bool operator!=(Vector2 a);
};

#endif //ARDUINOGAME_VECTOR2_H
