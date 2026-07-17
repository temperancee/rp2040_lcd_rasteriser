#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#include <stdint.h>
#include "math.h"

#define Q16_SHIFT 16
#define Q16_MASK ((1 << SHIFT_AMOUNT) - 1)
#define Q16_ONE (1 << Q16_SHIFT)
#define Q16_HALF (1 << (Q16_SHIFT - 1))

typedef int32_t q16;

// Conversion functions - only to be used on constants, so values get 
// precomputed at compile time (especially important for the float conversion!)
// Note the float conversion performs rounding

#define Q16_TO_INT(x) ( (int32_t) (x >> 16) )
#define INT_TO_Q16(x) ( (q16) (x << 16) )
#define FLOAT_TO_Q16(f) ( (q16) ((f >= 0.f) ?  f * (float)Q16_ONE + 0.5f : f * (float)Q16_ONE - 0.5f) )

// WARNING: NOT TO BE USED AT RUNTIME - for testing only
static double q16_to_double(q16 x)
{
    // integer part
    int32_t i = x >> 16;
    // decimal part
    int32_t d = x & 0x0000ffff;
    double sum = i;
    for (int shift = 0; shift < 16; shift++) {
        if ( d & (0x1 << shift)) {
            sum += pow(2, -(16 - shift));
        }
    }
    return sum;
}

// Conversion functions for variables whose values can only be known
// at runtime

static inline int32_t q16_to_int(q16 x)
{
    return x >> 16;
}

static inline q16 int_to_q16(int32_t x)
{
    return x << 16;
}

// Operations

// TODO: Introduce the more efficient ASM multiplication as used in RP2040 DOOM
static inline q16 q16_mul(q16 x, q16 y)
{
    return (q16) ( (((int64_t) x) * y) >> Q16_SHIFT );
}

static inline q16 q16_div(q16 x, q16 y)
{
    return (q16) ( (((int64_t) x) << Q16_SHIFT) / y );
}

static inline q16 maxq16(q16 x, q16 y)
{
    return (x > y) ? x : y;
}

static inline q16 minq16(q16 x, q16 y)
{
    return (x < y) ? x : y;
}

#endif // _FIXED_POINT_H_
