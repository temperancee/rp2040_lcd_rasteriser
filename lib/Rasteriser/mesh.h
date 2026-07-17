#ifndef _MESH_H_
#define _MESH_H_

#include <stdint.h>
#include <stddef.h>

#include "types/misc.h"


typedef struct {
    vertex const *vertices;
    uint32_t const *indices;
    uint32_t count; // If indices is non NULL, this specified the no. of indices, otherwise, it is the number of vertices in vertices
} mesh;


#endif // !_MESH_H_
