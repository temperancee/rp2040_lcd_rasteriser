#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} col3ub;

static inline col3ub hex_to_col3(uint16_t hex)
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


/**
 * @brief Converts a col3ub colour to an 8 bit colour
 * @param col - The colour to convert
 * @return col in RGB332 format
 */
static inline uint8_t col3_to_hex(col3ub col)
{
    uint8_t r = (col.r*7)/255;
    uint8_t g = (col.g*7)/255;
    uint8_t b = (col.b*3)/255;

    return (r << 5) | (g << 2) | b;
}

#endif  // _COLOUR_H_
