#include "Vector2.h"
#include "FastMath.h"

Vector2::Vector2() : x(0), y(0) {

}

Vector2::Vector2(float xx, float yy) : x(xx), y(yy) {

}

void Vector2::zero() {
    x = 0;
    y = 0;
}

bool Vector2::is_zero() const {
    return x == 0 && y == 0;
}

float Vector2::length() {
    return (float)sqrt(length_sq());
}

float Vector2::length_sq() {
    return x * x + y * y;
}

void Vector2::normalize() {
    float len = length();
    x /= len;
    y /= len;
}

Vector2 Vector2::normalized() {
    Vector2 r = *this;
    r.normalize();
    return r;
}

float Vector2::dot(const Vector2 &v2) const {
    return x * v2.x + y * v2.y;
}

float Vector2::cross(const Vector2 &v2) const {
    return x * v2.y - v2.x * y;
}

Vector2 Vector2::operator=(Vector2 a) {
    x = a.x;
    y = a.y;
    return a;
}

Vector2 Vector2::operator+(Vector2 a) {
    return Vector2(x + a.x, y + a.y);
}

Vector2 Vector2::operator-(Vector2 a) {
    return Vector2(x - a.x, y - a.y);
}

Vector2 Vector2::operator/(float scalar) {
    return Vector2(x / scalar, y / scalar);
}

bool Vector2::operator==(Vector2 a) {
    return a.x == x && a.y == y;
}

bool Vector2::operator!=(Vector2 a) {
    return a.x != x || a.y != y;
}

Vector2 Vector2::operator*(float multiplier) {
    return Vector2(x * multiplier, y * multiplier);
}

Vector2 Vector2::operator*(Vector2 multiplier) {
    return Vector2(x * multiplier.x, y * multiplier.y);
}

Vector2 Vector2::operator+=(Vector2 a) {
    x = x + a.x;
    y = y + a.y;

    return *this;
}

Vector2 Vector2::operator-()
{
    return Vector2(-x, -y);
}
