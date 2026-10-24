#include <math.h>

#include "3dtransform.h"

Mat4 mat4_identity(void)
{
    Mat4 m = {{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat4 mat4_translate(float tx, float ty, float tz)
{
    Mat4 m = mat4_identity();

    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;

    return m;
}

Mat4 mat4_scale(float sx, float sy, float sz)
{
    Mat4 m = {{
        {sx,   0.0f, 0.0f, 0.0f},
        {0.0f, sy,   0.0f, 0.0f},
        {0.0f, 0.0f, sz,   0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat4 mat4_rotate_x(float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    Mat4 m = {{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, c,   -s,    0.0f},
        {0.0f, s,    c,    0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat4 mat4_rotate_y(float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    Mat4 m = {{
        { c,   0.0f, s,    0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {-s,   0.0f, c,    0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    return m;
}

Mat4 mat4_rotate_z(float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    Mat4 m = {{
        {c,   -s,   0.0f, 0.0f},
        {s,    c,   0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    return m;
}

// Standard OpenGL perspective matrix.
// The camera looks down -z, so put the object at a negative z.
Mat4 mat4_perspective(
    float fov_y,
    float aspect,
    float near_plane,
    float far_plane
)
{
    float f = 1.0f / tanf(fov_y * 0.5f);

    Mat4 m = {{{0}}};

    m.m[0][0] = f / aspect;
    m.m[1][1] = f;
    m.m[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
    m.m[2][3] =
        (2.0f * far_plane * near_plane) / (near_plane - far_plane);
    m.m[3][2] = -1.0f;

    return m;
}

Mat4 mat4_mul(Mat4 a, Mat4 b)
{
    Mat4 result = {{{0}}};

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int k = 0; k < 4; k++) {
                result.m[row][col] +=
                    a.m[row][k] * b.m[k][col];
            }
        }
    }

    return result;
}

Vec4 mat4_apply(Mat4 m, Vec4 p)
{
    Vec4 result;

    result.x =
        m.m[0][0] * p.x +
        m.m[0][1] * p.y +
        m.m[0][2] * p.z +
        m.m[0][3] * p.w;

    result.y =
        m.m[1][0] * p.x +
        m.m[1][1] * p.y +
        m.m[1][2] * p.z +
        m.m[1][3] * p.w;

    result.z =
        m.m[2][0] * p.x +
        m.m[2][1] * p.y +
        m.m[2][2] * p.z +
        m.m[2][3] * p.w;

    result.w =
        m.m[3][0] * p.x +
        m.m[3][1] * p.y +
        m.m[3][2] * p.z +
        m.m[3][3] * p.w;

    return result;
}

// The perspective divide turns clip space into NDC.
void transform_vertices_3d(
    const float *input,
    float *output,
    size_t vertex_count,
    Mat4 transform
)
{
    for (size_t i = 0; i < vertex_count; i++) {

        Vec4 p = {
            input[i * 3],
            input[i * 3 + 1],
            input[i * 3 + 2],
            1.0f
        };

        Vec4 transformed =
            mat4_apply(transform, p);

        if (transformed.w != 0.0f) {
            transformed.x /= transformed.w;
            transformed.y /= transformed.w;
            transformed.z /= transformed.w;
        }

        output[i * 3] =
            transformed.x;

        output[i * 3 + 1] =
            transformed.y;

        output[i * 3 + 2] =
            transformed.z;
    }
}
