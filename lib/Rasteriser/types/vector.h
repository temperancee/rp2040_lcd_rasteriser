#ifndef _VECTOR_H_
#define _VECTOR_H_


typedef struct {
    float x, y, z;
} vec3f;

typedef struct {
    float x, y, z, w;
} vec4f;

// Convert a 3 vector to a 4 vector with the final element = 0
inline vec4f as_vector(vec3f const *v)
{
    return (vec4f) {v->x, v->y, v->z, 0.f};
}

// Convert a 3 vector to a 4 vector with the final element = 1
inline vec4f as_point(vec3f const *v)
{
    return (vec4f) {v->x, v->y, v->z, 1.f};
}


#endif  // _VECTOR_H_
