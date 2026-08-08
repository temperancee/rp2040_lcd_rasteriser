#ifndef _DELAY_H_
#define _DELAY_H_

#include <pico/time.h>
#include <stdint.h>

static inline void Delay_ms(uint32_t xms)
{
#ifdef NDEBUG
    sleep_ms(xms);
#else
    // If this is a debug build, use the blocking sleep function,
    // so we can step through/over it without GDB hanging
    busy_wait_ms(xms);
#endif
}

static inline void Delay_us(uint32_t xus)
{
    sleep_us(xus);
}

#endif // _DELAY_H_
