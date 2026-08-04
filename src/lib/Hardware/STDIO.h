/**
 * This file provides a wrapper for stdio_init_all(). I am not sure if
 * we need to call this, but the manufacturer provided code does, and I
 * am not certain of its scope, so to be safe, we call it.
 */

#ifndef _STDIO_H_
#define _STDIO_H_

#include <pico/stdio.h>

static inline void STDIO_INIT_ALL(void)
{
    stdio_init_all();
}

#endif // _STDIO_H_
