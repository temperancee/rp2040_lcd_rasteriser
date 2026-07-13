#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <stdint.h>

#include "types/vector.h"

typedef struct {
    uint8_t xmin, ymin, xmax, ymax;
} viewport;

inline vec4f apply(viewport const *vp, vec4f v)
{
    v.x = vp->xmin + (vp->xmax - vp->xmin)*(0.5f + 0.5f*v.x);
    v.y = vp->ymin + (vp->ymax - vp->ymin)*(0.5f + 0.5f*v.y);

    return v;
}

#endif  // _VIEWPORT_H_
