#include "Matrix4.h"

Matrix4::Matrix4() : Matrix4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
) {
}

Matrix4::Matrix4(float v11, float v12, float v13, float v14,
                 float v21, float v22, float v23, float v24,
                 float v31, float v32, float v33, float v34,
                 float v41, float v42, float v43, float v44) :
    m11(v11), m12(v12), m13(v13), m14(v14),
    m21(v21), m22(v22), m23(v23), m24(v24),
    m31(v31), m32(v32), m33(v33), m34(v34),
    m41(v41), m42(v42), m43(v43), m44(v44) {
}

Matrix4 Matrix4::operator*(Matrix4 &b) {
    return
        {
            (m11 * b.m11) + (m12 * b.m21) + (m13 * b.m31) + (m14 * b.m41),
            (m11 * b.m12) + (m12 * b.m22) + (m13 * b.m32) + (m14 * b.m42),
            (m11 * b.m13) + (m12 * b.m23) + (m13 * b.m33) + (m14 * b.m43),
            (m11 * b.m14) + (m12 * b.m24) + (m13 * b.m34) + (m14 * b.m44),

            (m21 * b.m11) + (m22 * b.m21) + (m23 * b.m31) + (m24 * b.m41),
            (m21 * b.m12) + (m22 * b.m22) + (m23 * b.m32) + (m24 * b.m42),
            (m21 * b.m13) + (m22 * b.m23) + (m23 * b.m33) + (m24 * b.m43),
            (m21 * b.m14) + (m22 * b.m24) + (m23 * b.m34) + (m24 * b.m44),

            (m31 * b.m11) + (m32 * b.m21) + (m33 * b.m31) + (m34 * b.m41),
            (m31 * b.m12) + (m32 * b.m22) + (m33 * b.m32) + (m34 * b.m42),
            (m31 * b.m13) + (m32 * b.m23) + (m33 * b.m33) + (m34 * b.m43),
            (m31 * b.m14) + (m32 * b.m24) + (m33 * b.m34) + (m34 * b.m44),

            (m41 * b.m11) + (m42 * b.m21) + (m43 * b.m31) + (m44 * b.m41),
            (m41 * b.m12) + (m42 * b.m22) + (m43 * b.m32) + (m44 * b.m42),
            (m41 * b.m13) + (m42 * b.m23) + (m43 * b.m33) + (m44 * b.m43),
            (m41 * b.m14) + (m42 * b.m24) + (m43 * b.m34) + (m44 * b.m44)
        };
}

Matrix4 matrix_look_at(Vector3 position, Vector3 target, Vector3 up) {
    Vector3 vector = (position - target).normalized();
    Vector3 vector2 = up.cross(vector).normalized();
    Vector3 vector3 = vector.cross(vector2);

    return
        {
            vector2.x, vector3.x, vector.x, 0.0f,
            vector2.y, vector3.y, vector.y, 0.0f,
            vector2.z, vector3.z, vector.z, 0.0f,
            -vector2.dot(position), -vector3.dot(position),
            -vector.dot(position), 1.0f
        };
}

Matrix4 matrix_perspective(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {
    Matrix4 result;
    if ((fieldOfView <= 0) || (fieldOfView >= PI) ||
        nearPlaneDistance <= 0 || farPlaneDistance <= 0 ||
        nearPlaneDistance >= farPlaneDistance) {
        return Matrix4();
    }
    float num = (float) (1.0f / (tanf((fieldOfView * 0.5f))));
    float num9 = num / aspectRatio;
    result.m11 = num9;
    result.m12 = result.m13 = result.m14 = 0;
    result.m22 = num;
    result.m21 = result.m23 = result.m24 = 0;
    result.m31 = result.m32 = 0.0f;
    result.m33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    result.m34 = -1;
    result.m41 = result.m42 = result.m44 = 0;
    result.m43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);

    return result;
}

Matrix4 matrix_scale(float x, float y, float z) {
    return
        {
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1
        };
}

Matrix4 matrix_translation(float x, float y, float z) {
    return
        {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1
        };
}

Matrix4 matrix_rotation_y(float radians) {
    Matrix4 result;

    float val1 = (float) cosf(radians);
    float val2 = (float) sinf(radians);

    result.m11 = val1;
    result.m13 = -val2;
    result.m31 = val2;
    result.m33 = val1;

    return result;
}

Matrix4 matrix_rotation_z(float radians) {
    Matrix4 result;

    float val1 = (float) cosf(radians);
    float val2 = (float) sinf(radians);

    result.m11 = val1;
    result.m12 = val2;
    result.m21 = -val2;
    result.m22 = val1;

    return result;
}

Matrix4 matrix_rotation_x(float radians) {
    Matrix4 result;

    float val1 = (float) cosf(radians);
    float val2 = (float) sinf(radians);

    result.m22 = val1;
    result.m23 = val2;
    result.m32 = -val2;
    result.m33 = val1;

    return result;
}