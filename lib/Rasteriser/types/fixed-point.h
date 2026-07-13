#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#include <stdint.h>

#define SHIFT_AMT 16
#define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1)

typedef int32_t fix16;

// fix16 fix16_add(fix16 x, fix16 y);
// fix16 fix16_sub(fix16 x, fix16 y);
// fix16 fix16_mul(fix16 x, fix16 y);
// fix16 fix16_div(fix16 x, fix16 y);

#endif // _FIXED_POINT_H_
