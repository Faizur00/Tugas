#include <math.h>

#include "transform.h"

Mat3 mat3_identity(void)
{
    Mat3 m = {{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat3 translate(float tx, float ty)
{
    Mat3 m = mat3_identity();

    m.m[0][2] = tx;
    m.m[1][2] = ty;

    return m;
}

Mat3 scale(float sx, float sy)
{
    Mat3 m = {{
        {sx,   0.0f, 0.0f},
        {0.0f, sy,   0.0f},
        {0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat3 rotate(float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    Mat3 m = {{
        {c,   -s,  0.0f},
        {s,    c,  0.0f},
        {0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat3 shear_x(float shx)
{
    Mat3 m = {{
        {1.0f, shx,  0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat3 shear_y(float shy)
{
    Mat3 m = {{
        {1.0f, 0.0f, 0.0f},
        {shy,  1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat3 reflect_x(void)
{
    return scale(1.0f, -1.0f);
}

Mat3 reflect_y(void)
{
    return scale(-1.0f, 1.0f);
}

Mat3 reflect_origin(void)
{
    return scale(-1.0f, -1.0f);
}

Mat3 mat3_mul(Mat3 a, Mat3 b)
{
    Mat3 result = {{{0}}};

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            for (int k = 0; k < 3; k++) {
                result.m[row][col] +=
                    a.m[row][k] * b.m[k][col];
            }
        }
    }

    return result;
}

Vec2 mat3_apply(Mat3 m, Vec2 p)
{
    Vec2 result;

    result.x =
        m.m[0][0] * p.x +
        m.m[0][1] * p.y +
        m.m[0][2];

    result.y =
        m.m[1][0] * p.x +
        m.m[1][1] * p.y +
        m.m[1][2];

    return result;
}


void transform_vertices(
    const float *input,
    float *output,
    size_t vertex_count,
    Mat3 transform
)
{
    for (size_t i = 0; i < vertex_count; i++) {

        Vec2 p = {
            input[i * 2],
            input[i * 2 + 1]
        };

        Vec2 transformed =
            mat3_apply(transform, p);

        output[i * 2] =
            transformed.x;

        output[i * 2 + 1] =
            transformed.y;
    }
}
