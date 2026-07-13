#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "vector.h"
#include <stdint.h>

typedef struct {
    float elements[16];
} matrix4f;

inline matrix4f mat4_id()
{
    return (matrix4f) {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

inline matrix4f homog_id_xy(int x, int y)
{
    return (matrix4f) {
        1.f, 0.f, 0.f, (float) x,
        0.f, 1.f, 0.f, (float) y,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

inline vec4f mat_vec_mult4f(matrix4f const *m, vec4f const *v)
{
    vec4f res;

    res.x = m->elements[ 0] * v->x + m->elements[ 1] * v->y + m->elements[ 2] * v->z + m->elements[ 3] * v->w;
    res.y = m->elements[ 4] * v->x + m->elements[ 5] * v->y + m->elements[ 6] * v->z + m->elements[ 7] * v->w;
    res.z = m->elements[ 8] * v->x + m->elements[ 9] * v->y + m->elements[10] * v->z + m->elements[11] * v->w;
    res.w = m->elements[12] * v->x + m->elements[13] * v->y + m->elements[14] * v->z + m->elements[15] * v->w;

    return res;
}

#endif  // _MATRIX_H_
