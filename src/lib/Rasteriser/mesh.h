#ifndef _MESH_H_
#define _MESH_H_

#include <stdint.h>
#include <stddef.h>

#include "types/misc.h"


typedef struct {
    vertex const *vertices;
    uint32_t const *indices;
    // If indices is non NULL, count specifies the no. of indices,
    // otherwise, it is the number of vertices
    uint32_t count; 
} mesh;


#endif // !_MESH_H_
