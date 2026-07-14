#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "fixed-point.h"
#include "vector.h"
#include <stdint.h>

typedef struct {
    q16 elements[16];
} matrix4q16;

static inline matrix4q16 mat4_id()
{
    return (matrix4q16) {
        Q16_ONE, 0, 0, 0,
        0, Q16_ONE, 0, 0,
        0, 0, Q16_ONE, 0,
        0, 0, 0, Q16_ONE,
    };
}

static inline matrix4q16 homog_id_xy(q16 x, q16 y)
{
    return (matrix4q16) {
        Q16_ONE, 0, 0, x,
        0, Q16_ONE, 0, y,
        0, 0, Q16_ONE, 0,
        0, 0, 0, Q16_ONE,
    };
}

// TODO: Introduce the more efficient ASM multiplication as used in RP2040 DOOM
static inline vec4q16 mat_vec_mult4q16(matrix4q16 const *m, vec4q16 const *v)
{
    vec4q16 res;

    res.x = q16_mul(m->elements[ 0], v->x) + q16_mul(m->elements[ 1], v->y) + q16_mul(m->elements[ 2], v->z) + q16_mul(m->elements[ 3], v->w);
    res.y = q16_mul(m->elements[ 4], v->x) + q16_mul(m->elements[ 5], v->y) + q16_mul(m->elements[ 6], v->z) + q16_mul(m->elements[ 7], v->w);
    res.z = q16_mul(m->elements[ 8], v->x) + q16_mul(m->elements[ 9], v->y) + q16_mul(m->elements[10], v->z) + q16_mul(m->elements[11], v->w);
    res.w = q16_mul(m->elements[12], v->x) + q16_mul(m->elements[13], v->y) + q16_mul(m->elements[14], v->z) + q16_mul(m->elements[15], v->w);

    return res;
}

#endif  // _MATRIX_H_
