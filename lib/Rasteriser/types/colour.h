#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} col3ub;

inline col3ub hex_to_col3(uint16_t hex)
{
    // Extract the 5 red bits, 6 green bits, and 5 blue bits
    uint8_t r = hex >> 11;
    uint8_t g = 0x07ff & (hex >> 5);
    uint8_t b = 0x001f & hex;

    // Normalise
    float r_norm = (float) r / 31;
    float g_norm = (float) g / 63;
    float b_norm = (float) b / 31;

    return (col3ub) {r_norm, g_norm, b_norm};
}


inline uint16_t col3_to_hex(col3ub col)
{
    uint8_t r = (col.r*31)/255;
    uint8_t g = (col.g*63)/255;
    uint8_t b = (col.b*31)/255;

    uint16_t x = r << 11;
    uint16_t y = x | (g << 5);
    uint16_t z = y | b;

    return z;
}

#endif  // _COLOUR_H_
