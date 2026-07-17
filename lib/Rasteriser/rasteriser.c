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
    for (uint16_t vertex_idx = 0; vertex_idx + 2 < cmd->mesh.count; vertex_idx += 3) {

        uint32_t i0 = vertex_idx + 0;
        uint32_t i1 = vertex_idx + 1;
        uint32_t i2 = vertex_idx + 2;

        // If we are using index based vertex selection
        if (cmd->mesh.indices) {
            i0 = cmd->mesh.indices[i0];
            i1 = cmd->mesh.indices[i1];
            i2 = cmd->mesh.indices[i2];
        }

        // Get the colours (get at the same time as vertices for efficiency)
        col3ub c0 = cmd->mesh.vertices[i0].col;
        col3ub c1 = cmd->mesh.vertices[i1].col;
        col3ub c2 = cmd->mesh.vertices[i2].col;

        // First, turn the vertex positions to 4D homogenous points 
        vec4q16 v0 = as_point(&cmd->mesh.vertices[i0].pos);
        vec4q16 v1 = as_point(&cmd->mesh.vertices[i1].pos);
        vec4q16 v2 = as_point(&cmd->mesh.vertices[i2].pos);
    
        // Now apply the transform (note, we can't take the address of the return 
        // value from as_point directly, because it _has no address_. Thus we had
        // to instantiate the above variables first)
        v0 = mat_vec_mult4q16(&cmd->transform, &v0);
        v1 = mat_vec_mult4q16(&cmd->transform, &v1);
        v2 = mat_vec_mult4q16(&cmd->transform, &v2);

        // Now, send the x, y, z values from [-1, 1] to the viewport's dimension
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

        // From now on, work only with integer vertices, to prevent overflow
        // This function adds 0.5 to the x y z coordinates to centre on the pixel
        // centre before conversion to integers
        vec4int v0_int = integerise_vertices(&v0);
        vec4int v1_int = integerise_vertices(&v1);
        vec4int v2_int = integerise_vertices(&v2);

        int32_t det012 = ((v1_int.x - v0_int.x) * (v2_int.y - v0_int.y)) - ((v1_int.y - v0_int.y) * (v2_int.x - v0_int.x));

        // Guard against 0 area triangles
        if (det012 == 0) continue;

        // Make sure triangle is counterclockwise (ccw)
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
            vec4int tempv = v1_int;
            v1_int = v2_int;
            v2_int = tempv;
            // Swap colours
            col3ub tempc = c1;
            c1 = c2;
            c2 = tempc;
            
        }

        // Pre compute the reciprocal of det012 for faster Barycentric
        // coordinate computation (divisions are slow on Cortex-M0+)
        // Use Q1.31
        uint32_t inv_det = (uint32_t)((1ULL << 31) / (uint32_t)det012);

        // Assign a colour for each pixel in the box
        for (uint16_t y = min_y; y <= max_y; y++) {
            for (uint16_t x = min_x; x <= max_x; x++) {
                vec3s32 p = {x, y, 0};

                // Compute unnormalised Barycentric weights
                int32_t det12p = edge_function(&v1_int, &v2_int, &p);
                int32_t det20p = edge_function(&v2_int, &v0_int, &p);
                int32_t det01p = edge_function(&v0_int, &v1_int, &p);

                // If p inside triangle, draw pixel
                // Typically, you'd check that p is to the 
                // right of the triangle edges, but since
                // the origin is in the top left (i.e., y-coords
                // increase as you go down, not up), we need to
                // check if p is to the left of the triangles edges,
                // which is equivalent to w1, w2, w3 <= 0
                if (det12p >= 0 && det20p >= 0 && det01p >= 0) {

                    // Compute Barycentric weights
                    // inv_det is in Q1.31, so a shift >> 15 moves us to Q16.16
                    q16 const w0 = (q16) (((uint64_t) det12p * inv_det) >> 15);
                    q16 const w1 = (q16) (((uint64_t) det20p * inv_det) >> 15);
                    q16 const w2 = (q16) (((uint64_t) det01p * inv_det) >> 15);

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
