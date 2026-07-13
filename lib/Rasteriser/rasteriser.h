#ifndef _RASTERISER_H_
#define _RASTERISER_H_

#include <stdint.h>
#include <stdint.h>

#include "draw_command.h"
#include "image_view.h"
#include "types/vector.h"
#include "viewport.h"


float edge_function(vec4f *a, vec4f *b, vec3f *p);
void draw(viewport const *view, draw_command const *cmd);

#endif // !_RASTERISER_H_
