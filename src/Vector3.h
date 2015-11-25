#ifndef ARDUINOGAME_VECTOR3_H
#define ARDUINOGAME_VECTOR3_H

#include <math.h>
#include "Matrix4.h"

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3();

    Vector3(float xx, float yy, float zz);

    inline void zero();

    inline bool is_zero() const;

    inline float length();

    inline float length_sq();

    inline void normalize();

    inline Vector3 normalized();

    inline float dot(const Vector3 &v3) const;

    inline Vector3 cross(const Vector3 &v3) const;

    inline Vector3 transform(const struct Matrix4 &m) const;

    inline Vector3 operator=(Vector3 a);

    inline Vector3 operator+(Vector3 a);

    inline Vector3 operator-(Vector3 a);

    inline Vector3 operator/(float scalar);

    inline bool operator==(Vector3 a);

    inline bool operator!=(Vector3 a);
};

#endif //ARDUINOGAME_VECTOR3_H
