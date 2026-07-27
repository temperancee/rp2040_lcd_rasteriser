#ifndef _RASTERISER_H_
#define _RASTERISER_H_

#include <stdint.h>
#include <stdint.h>

#include "draw_command.h"
#include "types/fixed-point.h"
#include "types/vector.h"


/**
 * @brief Converts a vector from normalised device coordinates to the screen's coordinate system. Currently only converts the x and y components.
 * @param v - the vector to be converted
 * @return v with its x and y coordinates given in screen space
 */
static inline vec4q16 ndc_to_screen(vec4q16 v)
{
    v.x = 120 * v.x + INT_TO_Q16(120);
    v.y = 120 * v.y + INT_TO_Q16(120);
    return v;
}

/**
 * @brief Computes the determinant between b - a and p - a
 * @param a - a pointer to a vector which represents the position of a vertex
 * @param b - a pointer to a vector which represents the position of a vertex
 * @param p - a pointer to a vector which represents the position of a point in the triangle being drawn
 * @return det(b-a, p-a)
 */
static inline int32_t edge_function(vec4int *a, vec4int *b, vec3s32 *p)
{
    vec3s32 ab = { b->x - a->x, b->y - a->y, 0};
    vec3s32 ap = { p->x - a->x, p->y - a->y, 0};
    return (ab.x * ap.y) - (ab.y * ap.x);
}

/**
 * @brief Draws a mesh onto the screen, following the parameters of cmd
 * @param cmd - a pointer to a draw_command object, this contains the parameters of the mesh to draw
 */
void draw(draw_command const *cmd);

#endif // !_RASTERISER_H_
