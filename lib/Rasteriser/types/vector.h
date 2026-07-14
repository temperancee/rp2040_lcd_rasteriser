#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "fixed-point.h"
#include <stdint.h>

typedef struct {
    q16 x, y, z;
} vec3q16;

typedef struct {
    uint8_t x, y, z;
} vec3ub;

typedef struct {
    int16_t x, y, z;
} vec3s16;

typedef struct {
    q16 x, y, z, w;
} vec4q16;

typedef struct {
    uint8_t x, y, z, w;
} vec4ub;

// Convert a 3 vector to a 4 vector with the final element = 0
static inline vec4q16 as_vector(vec3q16 const *v)
{
    return (vec4q16) {v->x, v->y, v->z, (q16) 0};
}

// Convert a 3 vector to a 4 vector with the final element = 1
static inline vec4q16 as_point(vec3q16 const *v)
{
    return (vec4q16) {v->x, v->y, v->z, (q16) (1 << 16)};
}


#endif  // _VECTOR_H_
