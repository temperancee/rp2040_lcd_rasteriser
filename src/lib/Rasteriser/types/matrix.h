#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "fixed-point.h"
#include "vector.h"
#include <stdint.h>
#include "angles.h"

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

static inline matrix4q16 mat_mat_multq16(matrix4q16 const *m1, matrix4q16 const *m2)
{
    matrix4q16 result = {0};

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            for (int k=0; k < 4; k++)
                result.elements[4*i + j] += q16_mul(m1->elements[4*i + k], m2->elements[4*k + j]);
        }
    }
    return result;
}

static inline vec4q16 mat_vec_mult4q16(matrix4q16 const *m, vec4q16 const *v)
{
    vec4q16 res = {0};

    res.x = q16_mul(m->elements[ 0], v->x) + q16_mul(m->elements[ 1], v->y) + q16_mul(m->elements[ 2], v->z) + q16_mul(m->elements[ 3], v->w);
    res.y = q16_mul(m->elements[ 4], v->x) + q16_mul(m->elements[ 5], v->y) + q16_mul(m->elements[ 6], v->z) + q16_mul(m->elements[ 7], v->w);
    res.z = q16_mul(m->elements[ 8], v->x) + q16_mul(m->elements[ 9], v->y) + q16_mul(m->elements[10], v->z) + q16_mul(m->elements[11], v->w);
    res.w = q16_mul(m->elements[12], v->x) + q16_mul(m->elements[13], v->y) + q16_mul(m->elements[14], v->z) + q16_mul(m->elements[15], v->w);

    return res;
}

// Transforms

static inline matrix4q16 translate(vec3q16 *v)
{
    return (matrix4q16) {
        Q16_ONE, 0, 0, v->x,
        0, Q16_ONE, 0, v->y,
        0, 0, Q16_ONE, v->z,
        0, 0, 0, Q16_ONE,
    };
}

static inline matrix4q16 scale(vec3q16 *v)
{
    return (matrix4q16) {
        v->x, 0, 0, 0,
        0, v->y, 0, 0,
        0, 0, v->z, 0,
        0, 0, 0, Q16_ONE,
    };
}


static inline matrix4q16 scale_by_scalar(q16 s)
{
    return (matrix4q16) {
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, Q16_ONE,
    };
}

static inline matrix4q16 rotateXY(int angle)
{
    return (matrix4q16) {
        cos_q16(angle), -sin_q16(angle), 0, 0,
        sin_q16(angle), cos_q16(angle), 0, 0,
        0, 0, Q16_ONE, 0,
        0, 0, 0, Q16_ONE,
    };
}

static inline matrix4q16 rotateYZ(int angle)
{
    return (matrix4q16) {
        Q16_ONE, 0, 0, 0,
        0, cos_q16(angle), -sin_q16(angle), 0,
        0, sin_q16(angle), cos_q16(angle), 0,
        0, 0, 0, Q16_ONE,
    };
}

static inline matrix4q16 rotateXZ(int angle)
{
    return (matrix4q16) {
        cos_q16(angle), 0, sin_q16(angle), 0,
        0, Q16_ONE, 0, 0,
        -sin_q16(angle), 0, cos_q16(angle), 0,
        0, 0, 0, Q16_ONE,
    };
}

#endif  // _MATRIX_H_
