#ifndef _RASTERISER_H_
#define _RASTERISER_H_

#include <stdint.h>
#include <stdint.h>

#include "draw_command.h"
#include "types/fixed-point.h"
#include "types/vector.h"


static inline vec4q16 ndc_to_screen(vec4q16 v)
{
    // 1 << 15 is a half in fixed-point
    // TODO: This can be optimised further, but we need somewhere to
    // write down all of our weird fixed-point formulae - a translation
    // book so we can understand what they mean in normal maths terms

    // v.x = (240 - 0)*(Q16_HALF + v.x/2);
    // v.y = (240 - 0)*(Q16_HALF + v.y/2);
    v.x = 120 * v.x + INT_TO_Q16(120);
    v.y = 120 * v.y + INT_TO_Q16(120);

    return v;
}

static inline q16 edge_function(vec4q16 *a, vec4q16 *b, vec3q16 *p)
{
    vec3q16 ab = { b->x - a->x, b->y - a->y, 0};
    vec3q16 ap = { p->x - a->x, p->y - a->y, 0};
    return q16_mul(ab.x, ap.y) - q16_mul(ab.y, ap.x);
}

void draw(draw_command const *cmd);

#endif // !_RASTERISER_H_
