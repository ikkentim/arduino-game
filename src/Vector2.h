#ifndef ARDUINOGAME_VECTOR2_H
#define ARDUINOGAME_VECTOR2_H

#include <math.h>
#include "Matrix4.h"

struct Vector2 {
    float x;
    float y;

    Vector2();
    Vector2(float xx, float yy);
    inline void zero();
    inline bool is_zero() const;
    inline float length();
    inline float length_sq();
    inline void normalize();
    inline Vector2 normalized();
    inline float dot(const Vector2 &v2) const;
    inline float cross(const Vector2 &v2) const;
    inline Vector2 transform(const struct Matrix4 &m) const;
    inline Vector2 operator=(Vector2 a);
    inline Vector2 operator+(Vector2 a);
    inline Vector2 operator-(Vector2 a);
    inline Vector2 operator/(float scalar);
    inline bool operator==(Vector2 a);
    inline bool operator!=(Vector2 a);
};

#endif //ARDUINOGAME_VECTOR2_H
