#ifndef ARDUINOGAME_VECTOR3_H
#define ARDUINOGAME_VECTOR3_H

#include <math.h>

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {

    }

    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {

    }

    inline void zero() {
        x = 0;
        y = 0;
        z = 0;
    }

    inline bool is_zero() const {
        return x == 0 && y == 0 && z == 0;
    }

    inline float length() {
        return (float)sqrt(length_sq());
    }

    inline float length_sq() {
        return x * x + y * y + z * z;
    }

    inline void normalize() {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
    }

    inline Vector3 normalized() {
        Vector3 r = *this;
        r.normalize();
        return r;
    }

    inline float dot(const Vector3 &v3) const {
        return x*v3.x + y*v3.y + z * v3.z;
    }

    inline Vector3 cross(const Vector3 &v3) const {
        float xx = y * v3.z - v3.y * z;
        float yy = -(x * v3.z - v3.x * z);
        float zz = x * v3.y - v3.x * y;
        return Vector3(xx, yy, zz);
    }

    inline Vector3 operator=(Vector3 a) {
        x = a.x;
        y = a.y;
        z = a.z;
        return a;
    }

    inline Vector3 operator+(Vector3 a) {
        return Vector3(x + a.x, y + a.y, z + a.z);
    }

    inline Vector3 operator-(Vector3 a) {
        return Vector3(x - a.x, y - a.y, z - a.z);
    }

    inline Vector3 operator/(float scalar) {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    inline bool operator==(Vector3 a) {
        return a.x == x && a.y == y && a.z == z;
    }

    inline bool operator!=(Vector3 a) {
        return a.x != x || a.y != y || a.z != z;
    }
};

#endif //ARDUINOGAME_VECTOR3_H
