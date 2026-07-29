#ifndef _MISC_H_
#define _MISC_H_

#include <stdint.h>
#include "vector.h"
#include "colour.h"

typedef struct {
    vec3q16 pos;
    col3ub col;
} vertex;

static inline int minint(int x, int y)
{
    return (x < y ? x : y);
}

static inline int maxint(int x, int y)
{
    return (x < y ? y : x);
}

#endif  // _MISC_H_


