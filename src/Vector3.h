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

    void zero();

    bool is_zero() const;

    float length();

    float length_sq();

    void normalize();

    Vector3 normalized();

    float dot(const Vector3 &v3) const;

    Vector3 cross(const Vector3 &v3) const;

    Vector3 transform(const struct Matrix4 &m) const;

    Vector3 operator=(Vector3 a);

    Vector3 operator+(Vector3 a);

    Vector3 operator-(Vector3 a);

    Vector3 operator/(float scalar);

    bool operator==(Vector3 a);

    bool operator!=(Vector3 a);
};

#endif //ARDUINOGAME_VECTOR3_H
