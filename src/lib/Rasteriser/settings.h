// Settings for the draw command
#ifndef _SETTINGS_H_
#define _SETTINGS_H_

enum CullMode {
    // Backface culling
    // CW - cull clockwise oriented triangles
    // CCW - cull counterclockwise oriented triangles
    NO_CULL,
    CW,
    CCW
};

#endif  // _SETTINGS_H_
