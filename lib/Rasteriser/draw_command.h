#ifndef _DRAW_COMMAND_H_
#define _DRAW_COMMAND_H_

#include "mesh.h"
#include "settings.h"
#include "types/matrix.h"

typedef struct {
    mesh mesh;
    enum CullMode cull_mode;
    matrix4q16 transform;
} draw_command;

#endif  // _DRAW_COMMAND_H_
