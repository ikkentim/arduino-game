#ifndef ARDUINOGAME_MATRIX4_H
#define ARDUINOGAME_MATRIX4_H

#include "Vector3.h"

#define PI      (3.141593)

struct Matrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;

    Matrix4();

    Matrix4(float v11, float v12, float v13, float v14,
            float v21, float v22, float v23, float v24,
            float v31, float v32, float v33, float v34,
            float v41, float v42, float v43, float v44);

    Matrix4 operator*(Matrix4 &b);
};

Matrix4 matrix_look_at(struct Vector3 position, struct Vector3 target, struct Vector3 up);

Matrix4 matrix_perspective(float fov, float aspectRatio, float near, float far);

Matrix4 matrix_scale(float x, float y, float z);

Matrix4 matrix_translation(float x, float y, float z);

Matrix4 matrix_rotation_x(float radians);

Matrix4 matrix_rotation_y(float radians);

Matrix4 matrix_rotation_z(float radians);

#endif //ARDUINOGAME_MATRIX4_H
