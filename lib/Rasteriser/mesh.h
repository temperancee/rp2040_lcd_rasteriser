#ifndef _MESH_H_
#define _MESH_H_

#include <stdint.h>
#include <stddef.h>

#include "types/misc.h"


typedef struct {
    vertex const *vertices;
    uint16_t vertex_count;
} mesh;

// NOTE: This is currently unused and probably unnecessary
inline void initialise_mesh(mesh *m)
{
    m->vertices = NULL;
    m->vertex_count = 0;
}

#endif // !_MESH_H_
