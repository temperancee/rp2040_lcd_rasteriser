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
    int32_t x, y, z;
} vec3s32;

typedef struct {
    q16 x, y, z, w;
} vec4q16;

typedef struct {
    int32_t x, y, z, w;
} vec4int;

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

// Convert a q16 4 vector to an int32_t 4 vector
static inline vec4int vecq16_to_vec4int(vec4q16 const *v)
{
    return (vec4int) {q16_to_int(v->x), q16_to_int(v->y), q16_to_int(v->z), q16_to_int(v->w)};
}

#endif  // _VECTOR_H_
