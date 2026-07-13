#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>

typedef struct {
    uint8_t x, y, z;
} vec3ub;

typedef struct {
    int16_t x, y, z;
} vec3s16;

typedef struct {
    float x, y, z, w;
} vec4f;

// Convert a 3 vector to a 4 vector with the final element = 0
inline vec4f as_vector(vec3ub const *v)
{
    return (vec4f) {v->x, v->y, v->z, 0.f};
}

// Convert a 3 vector to a 4 vector with the final element = 1
inline vec4f as_point(vec3ub const *v)
{
    return (vec4f) {v->x, v->y, v->z, 1.f};
}


#endif  // _VECTOR_H_
