#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} col3ub;


// Converts col3ub to an 8 bit RBG332 colour
static inline uint8_t col3_to_hex(col3ub col)
{
    uint8_t r = (col.r*7)/255;
    uint8_t g = (col.g*7)/255;
    uint8_t b = (col.b*3)/255;
    return (r << 5) | (g << 2) | b;
}

#endif  // _COLOUR_H_
