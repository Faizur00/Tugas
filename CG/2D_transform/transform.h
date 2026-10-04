#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stddef.h>

typedef struct {
    float m[3][3];
} Mat3;

typedef struct {
    float x;
    float y;
} Vec2;

Mat3 mat3_identity(void);

Mat3 translate(float tx, float ty);

Mat3 scale(float sx, float sy);

Mat3 rotate(float angle);

Mat3 shear_x(float shx);

Mat3 shear_y(float shy);

Mat3 reflect_x(void);

Mat3 reflect_y(void);

Mat3 reflect_origin(void);

Mat3 mat3_mul(Mat3 a, Mat3 b);

Vec2 mat3_apply(Mat3 m, Vec2 p);

void transform_vertices(
    const float *input,
    float *output,
    size_t vertex_count,
    Mat3 transform
);

#endif
