#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#include <stdint.h>
#include "math.h"

#define Q16_SHIFT 16
#define Q16_MASK ((1 << SHIFT_AMOUNT) - 1)
#define Q16_ONE (1 << Q16_SHIFT)
#define Q16_HALF (1 << (Q16_SHIFT - 1))

typedef int32_t q16;

// Conversion functions - only to be used on constants, so values get 
// precomputed at compile time (especially important for the float conversion!)
// Note the float conversion performs rounding

/**
 * @brief Transform a Q16.16 number to an integer, truncating the fractional part
 * @param x - a Q16.16 number to truncate
 * @return x as an int
 */
#define Q16_TO_INT(x) ( (int32_t) (x >> 16) )

/**
 * @brief Transform an int to a Q16.16 fixed point number
 * @param x - an int
 * @return x as a Q16.16
 */
#define INT_TO_Q16(x) ( (q16) (x << 16) )

/**
 * @brief Transform a float to a Q16.16 fixed point number. This function is a macro so floating point numbers can be
 * entered for ease of programming, but be stored in fixed-point format for computational efficiency
 * @param x - a float
 * @return x as a Q16.16
 */
#define FLOAT_TO_Q16(f) ( (q16) ((f >= 0.f) ?  f * (float)Q16_ONE + 0.5f : f * (float)Q16_ONE - 0.5f) )

// WARNING: NOT TO BE USED AT RUNTIME - for testing only
static double q16_to_double(q16 x)
{
    // integer part
    int32_t i = x >> 16;
    // decimal part
    int32_t d = x & 0x0000ffff;
    double sum = i;
    for (int shift = 0; shift < 16; shift++) {
        if ( d & (0x1 << shift)) {
            sum += pow(2, -(16 - shift));
        }
    }
    return sum;
}

// Conversion functions for variables whose values can only be known
// at runtime


/**
 * @brief Convert Q16.16 fixed point number to int
 * @param x - the Q16.16 number to convert
 * @return x as an int
 */
static inline int32_t q16_to_int(q16 x)
{
    return x >> 16;
}

/**
 * @brief Convert an int to a Q16.16 fixed point number
 * @param x - the int to convert, must be no more than 16 bits long
 * @return x as a Q16.16 int
 */
static inline q16 int_to_q16(int32_t x)
{
    return x << 16;
}

// Operations

// TODO: Introduce the more efficient ASM multiplication as used in RP2040 DOOM
/**
 * @brief Multiply two Q16.16 fixed point numbers together
 * @param x - a Q16.16 fixed point number
 * @param y - a Q16.16 fixed point number
 * @return x*y
 */
static inline q16 q16_mul(q16 x, q16 y)
{
#if PICO_ON_DEVICE
    uint32_t tmp1, tmp2, tmp3;
    __asm__ volatile (
    ".syntax unified\n"
    "asrs   %[r_tmp1], %[r_y], #16 \n" // r_tmp1 = y_high
    "uxth   %[r_tmp2], %[r_x]      \n" // r_tmp2 = x_low
    "muls   %[r_tmp2], %[r_tmp1]   \n" // r_tmp2 = y_high * x_low
    "asrs   %[r_tmp3], %[r_x], #16 \n" // r_tmp3 = x_high
    "muls   %[r_tmp1], %[r_tmp3]   \n" // r_tmp1 = y_high * x_high
    "uxth   %[r_y], %[r_y]         \n" // r_y = y_low
    "uxth   %[r_x], %[r_x]         \n" // r_x = x_low
    "muls   %[r_x], %[r_y]         \n" // r_x = x_low * y_low
    "muls   %[r_y], %[r_tmp3]      \n" // r_y = y_low * x_high
    "add    %[r_y], %[r_tmp2]      \n" // r_y = y_low * x_high + y_high * x_low
    "lsls   %[r_tmp1], #16         \n" // r_tmp1 = (y_high * x_high) << 16
    "lsrs   %[r_x], #16            \n" // r_x = (x_low * y_low) >> 16
    "add    %[r_x], %[r_y]         \n" // r_x = (y_low * x_high + y_high * x_low) + ((x_low * y_low) >> 16)
    "add    %[r_x], %[r_tmp1]      \n" // r_x = ((y_high * x_high) << 16) + (y_low * x_high + y_high * x_low) + ((x_low * y_low) >> 16) = x * y
    : [r_x] "+l" (x), [r_y] "+l" (y), [r_tmp1] "=&l" (tmp1), [r_tmp2] "=&l" (tmp2), [r_tmp3] "=&l" (tmp3)
    :
    );
    // The "l" part means we can only access the low registers, i.e. r0-r7, since uxth, asrs, and muls only work on these registers
    // "+l" means we can read and write to the registers storing x and y
    // "=&l" means tmpx are allocated to registers other than the ones storing x and y (since we don't want these overwritten)
    return x;
#else
    return (q16) ( (((int64_t) x) * y) >> Q16_SHIFT );
#endif
}

/**
 * @brief Divide a Q16.16 fixed point number by another Q16.16
 * @param x - a Q16.16 fixed point number
 * @param y - a Q16.16 fixed point number
 * @return x divided by y
 */
static inline q16 q16_div(q16 x, q16 y)
{
    return (q16) ( (((int64_t) x) << Q16_SHIFT) / y );
}

/**
 * @brief Return the maximum of two Q16.16 numbers
 * @param x - a Q16.16 fixed point number
 * @param y - a Q16.16 fixed point number
 * @return The bigger of the two numbers
 */
static inline q16 maxq16(q16 x, q16 y)
{
    return (x > y) ? x : y;
}

/**
 * @brief Return the minimum of two Q16.16 numbers
 * @param x - a Q16.16 fixed point number
 * @param y - a Q16.16 fixed point number
 * @return The lesser of the two numbers
 */
static inline q16 minq16(q16 x, q16 y)
{
    return (x < y) ? x : y;
}

#endif // _FIXED_POINT_H_
