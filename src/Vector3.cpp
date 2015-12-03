#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0) {

}

Vector3::Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {

}

void Vector3::zero() {
    x = 0;
    y = 0;
    z = 0;
}

bool Vector3::is_zero() const {
    return x == 0 && y == 0 && z == 0;
}

float Vector3::length() {
    return (float)sqrt(length_sq());
}

float Vector3::length_sq() {
    return x * x + y * y + z * z;
}

void Vector3::normalize() {
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

Vector3 Vector3::normalized() {
    Vector3 r = *this;
    r.normalize();
    return r;
}

float Vector3::dot(const Vector3 &v3) const {
    return x*v3.x + y*v3.y + z * v3.z;
}

Vector3 Vector3::cross(const Vector3 &v3) const {
    float xx = y * v3.z - v3.y * z;
    float yy = -(x * v3.z - v3.x * z);
    float zz = x * v3.y - v3.x * y;
    return Vector3(xx, yy, zz);
}

Vector3 Vector3::transform(const struct Matrix4 &m) const {
    return Vector3(
        (x * m.m11) + (y * m.m21) + (z * m.m31) + m.m41,
        (x * m.m12) + (y * m.m22) + (z * m.m32) + m.m42,
        (x * m.m13) + (y * m.m23) + (z * m.m33) + m.m43
    );
}

Vector3 Vector3::operator=(Vector3 a) {
    x = a.x;
    y = a.y;
    z = a.z;
    return a;
}

Vector3 Vector3::operator+(Vector3 a) {
    return Vector3(x + a.x, y + a.y, z + a.z);
}

Vector3 Vector3::operator-(Vector3 a) {
    return Vector3(x - a.x, y - a.y, z - a.z);
}

Vector3 Vector3::operator/(float scalar) {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

bool Vector3::operator==(Vector3 a) {
    return a.x == x && a.y == y && a.z == z;
}

bool Vector3::operator!=(Vector3 a) {
    return a.x != x || a.y != y || a.z != z;
}