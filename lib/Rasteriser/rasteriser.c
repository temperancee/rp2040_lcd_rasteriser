#include <stdint.h>

#include "rasteriser.h"
#include "../GUI/GUI_Paint.h"
#include "settings.h"
#include "types/colour.h"
#include "types/fixed-point.h"
#include "types/vector.h"
#include "types/matrix.h"

void draw(draw_command const *cmd)
{
    // Loop through each triangle in the mesh
    for (uint16_t vertex_idx = 0; vertex_idx + 2 < cmd->mesh.vertex_count; vertex_idx += 3) {

        // Get the colours (get at the same time as vertices for efficiency)
        col3ub c0 = cmd->mesh.vertices[vertex_idx].col;
        col3ub c1 = cmd->mesh.vertices[vertex_idx+1].col;
        col3ub c2 = cmd->mesh.vertices[vertex_idx+2].col;

        // First, turn the vertex positions to 4D homogenous points 
        vec4q16 v0 = as_point(&cmd->mesh.vertices[vertex_idx].pos);
        vec4q16 v1 = as_point(&cmd->mesh.vertices[vertex_idx+1].pos);
        vec4q16 v2 = as_point(&cmd->mesh.vertices[vertex_idx+2].pos);
        
        // Now apply the transform (note, we can't take the address of the return 
        // value from as_point directly, because it _has no address_. Thus we had
        // to instantiate the above variables first)
        v0 = mat_vec_mult4q16(&cmd->transform, &v0);
        v1 = mat_vec_mult4q16(&cmd->transform, &v1);
        v2 = mat_vec_mult4q16(&cmd->transform, &v2);

        // Now, send the x, y, z values from [-1, 1] to the viewport's dimension: integers
        v0 = ndc_to_screen(v0);
        v1 = ndc_to_screen(v1);
        v2 = ndc_to_screen(v2);

        // Bounding boxes

        // First, account for the possibility that the viewport is not entirely
        // on the screen
        // uint16_t min_x = (uint16_t)fmaxf(viewport->xmin, 0);
        // uint16_t max_x = (uint16_t)fminf(viewport->xmax, Paint.Width) - 1;
        // uint16_t min_y = (uint16_t)fmaxf(viewport->ymin, 0);
        // uint16_t max_y = (uint16_t)fminf(viewport->ymax, Paint.Height) - 1;
        //
        // Then create bounding boxes around the vertices, accounting for the
        // possibility that the vertices are not in the viewport
        // min_x = (uint16_t)fmaxf(min_x, fminf(v2.x, fminf(v0.x, v1.x)));
        // max_x = (uint16_t)fminf(max_x, fmaxf(v2.x, fmaxf(v0.x, v1.x)));
        // min_y = (uint16_t)fmaxf(min_y, fminf(v2.y, fminf(v0.y, v1.y)));
        // max_y = (uint16_t)fminf(max_y, fmaxf(v2.y, fmaxf(v0.y, v1.y)));

        int32_t min_x = q16_to_int(minq16(v2.x, minq16(v0.x, v1.x)));
        int32_t max_x = q16_to_int(maxq16(v2.x, maxq16(v0.x, v1.x)));
        int32_t min_y = q16_to_int(minq16(v2.y, minq16(v0.y, v1.y)));
        int32_t max_y = q16_to_int(maxq16(v2.y, maxq16(v0.y, v1.y)));

        // Make sure triangle is counterclockwise (ccw)
        q16 det012 = q16_mul((v1.x - v0.x), (v2.y - v0.y)) - q16_mul((v1.y - v0.y), (v2.x - v0.x));
        bool const cw = (det012 < 0);

        // Determine what to do with this triangle given the backface
        // culling mode
        switch (cmd->cull_mode) {
            case NO_CULL:
                // No culling, so just break out of the switch case
                break;
            case CW:
                // Cull clockwise triangles. If this triangle is clockwise
                // we need to skip drawing it and move to the next
                if (cw)
                    continue;
                break;
            case CCW:
                // Cull counterclockwise triangles. If this triangle is
                // counterclockwise, we need to skip it and move on
                if (!cw)
                    continue;
                break;
        }

        // For triangles that have not been culled, but are clockwise
        // we need to make them counterclockwise for our triangle
        // rasterisation algorithm to work
        if (cw) {
            det012 = -det012;
            // Swap vertices
            q16 tempx = v1.x;
            q16 tempy = v1.y;
            v1.x = v2.x;
            v1.y = v2.y;
            v2.x = tempx;
            v2.y = tempy;
        }

        // Assign a colour for each pixel in the box
        for (uint16_t y = min_y; y <= max_y; y++) {
            for (uint16_t x = min_x; x <= max_x; x++) {
                vec3q16 p = {int_to_q16((int32_t) x) + Q16_HALF, int_to_q16((int32_t) y) + Q16_HALF, 0};

                // Compute unnormalised Barycentric weights
                q16 det12p = edge_function(&v1, &v2, &p);
                q16 det20p = edge_function(&v2, &v0, &p);
                q16 det01p = edge_function(&v0, &v1, &p);

                // If p inside triangle, draw pixel
                // Typically, you'd check that p is to the 
                // right of the triangle edges, but since
                // the origin is in the top left (i.e., y-coords
                // increase as you go down, not up), we need to
                // check if p is to the left of the triangles edges,
                // which is equivalent to w1, w2, w3 <= 0
                if (det12p >= 0 && det20p >= 0 && det01p >= 0) {

                    // Compute Barycentric weights
                    // TODO: w_i \in [-1, 1], so we can optimise this by using a smaller type
                    // BUG: These aren't being computed correctly
                    q16 const w0 = q16_div(det12p, det012);
                    q16 const w1 = q16_div(det20p, det012);
                    q16 const w2 = q16_div(det01p, det012);

                    col3ub interpolated_col;
                    interpolated_col.r = (uint8_t) q16_to_int(w0 * c0.r + w1 * c1.r + w2 * c2.r);
                    interpolated_col.g = (uint8_t) q16_to_int(w0 * c0.g + w1 * c1.g + w2 * c2.g);
                    interpolated_col.b = (uint8_t) q16_to_int(w0 * c0.b + w1 * c1.b + w2 * c2.b);
                    Paint_SetPixel(x, y, col3_to_hex(interpolated_col));
                }
            }
        }

    }
    
}
