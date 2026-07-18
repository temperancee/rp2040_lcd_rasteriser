#ifndef _RASTERISER_H_
#define _RASTERISER_H_

#include <stdint.h>
#include <stdint.h>

#include "draw_command.h"
#include "types/fixed-point.h"
#include "types/vector.h"


static inline vec4q16 ndc_to_screen(vec4q16 v)
{
    v.x = 120 * v.x + INT_TO_Q16(120);
    v.y = 120 * v.y + INT_TO_Q16(120);
    return v;
}

static inline int32_t edge_function(vec4int *a, vec4int *b, vec3s32 *p)
{
    vec3s32 ab = { b->x - a->x, b->y - a->y, 0};
    vec3s32 ap = { p->x - a->x, p->y - a->y, 0};
    return (ab.x * ap.y) - (ab.y * ap.x);
}

void draw(draw_command const *cmd);

#endif // !_RASTERISER_H_
