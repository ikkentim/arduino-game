#include "FastMath.h"
#include <math.h>
#include <stdint.h>

float fast_cos(float x, bool lessPrecision) {
    return fast_sin(x + 3.1415f / 2, lessPrecision);
}

float fast_sin(float x, bool lessPrecision) {
    while (x > 3.14159265359f) {
        x -= 6.28318530718f; // 2 pi
    }
    while (x < -3.14159265359f) {
        x += 6.28318530718f; // 2 pi
    }
    const float B = 1.27323954474f; // 4 / pi
    const float C = -0.40528473456f; // -4 / (pi * pi);

    float y = B * x + C * x * fabs(x);

    if (!lessPrecision) {
        const float Q = 0.775;
        const float P = 0.225;

        y = P * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)
    }

    return y;
}

float fast_sqrt(float x) {
    uint32_t i = *(uint32_t *) &x;

    // adjust bias
    i += 127 << 23;
    // approximation of square root
    i >>= 1;

    return *(float *) &i;
}
