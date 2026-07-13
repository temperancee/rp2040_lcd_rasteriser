#ifndef _RASTERISER_H_
#define _RASTERISER_H_

#include <stdint.h>
#include <stdint.h>

#include "draw_command.h"
#include "image_view.h"
#include "types/vector.h"


int16_t edge_function(vec4f *a, vec4f *b, vec3ub *p);
void draw(draw_command const *cmd);

#endif // !_RASTERISER_H_
