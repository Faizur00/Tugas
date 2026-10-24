#ifndef TRANSFORM_3D_H
#define TRANSFORM_3D_H

#include <stddef.h>

typedef struct {
    float m[4][4];
} Mat4;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

Mat4 mat4_identity(void);

Mat4 mat4_translate(float tx, float ty, float tz);

Mat4 mat4_scale(float sx, float sy, float sz);

Mat4 mat4_rotate_x(float angle);

Mat4 mat4_rotate_y(float angle);

Mat4 mat4_rotate_z(float angle);

Mat4 mat4_perspective(
    float fov_y,
    float aspect,
    float near_plane,
    float far_plane
);

Mat4 mat4_mul(Mat4 a, Mat4 b);

Vec4 mat4_apply(Mat4 m, Vec4 p);

void transform_vertices_3d(
    const float *input,
    float *output,
    size_t vertex_count,
    Mat4 transform
);

#endif
