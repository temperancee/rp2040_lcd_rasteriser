#include "cube.h"
#include "stdint.h"
#include "types/colour.h"
#include "types/vector.h"

vertex const vertices[] = {
    // -X face
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {0, 255, 255} },
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {0, 255, 255} },
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {0, 255, 255} },
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {0, 255, 255} },

    // +X face
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {255, 0, 0} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {255, 0, 0} },
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {255, 0, 0} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {255, 0, 0} },

    // -Y face
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {255, 0, 255} },
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {255, 0, 255} },
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {255, 0, 255} },
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {255, 0, 255} },

    // +Y face
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {0, 255, 0} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {0, 255, 0} },
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {0, 255, 0} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {0, 255, 0} },

    // -Z face
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {255, 255, 0} },
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF, -Q16_HALF}, (col3ub) {255, 255, 0} },
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {255, 255, 0} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF, -Q16_HALF}, (col3ub) {255, 255, 0} },

    // +Z face
    (vertex) { (vec3q16) {-Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {0, 0, 255} },
    (vertex) { (vec3q16) { Q16_HALF, -Q16_HALF,  Q16_HALF}, (col3ub) {0, 0, 255} },
    (vertex) { (vec3q16) {-Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {0, 0, 255} },
    (vertex) { (vec3q16) { Q16_HALF,  Q16_HALF,  Q16_HALF}, (col3ub) {0, 0, 255} },
};

uint32_t const cube_indices[] = {
    // -X face
     0,  2,  1,
     1,  2,  3,

    // +X face
     4,  5,  6,
     6,  5,  7,

    // -Y face
     8,  9, 10,
    10,  9, 11,

    // +Y face
    12, 14, 13,
    14, 15, 13,

    // -Z face
    16, 18, 17,
    17, 18, 19,

    // +Z face
    20, 21, 22,
    21, 23, 22,
};


mesh const cube = {
    .vertices = vertices,
    .indices = cube_indices,
    .count = 36,
};
