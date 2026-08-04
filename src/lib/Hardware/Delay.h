#ifndef _DELAY_H_
#define _DELAY_H_

#include <pico/time.h>
#include <stdint.h>

static inline void Delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

static inline void Delay_us(uint32_t us)
{
    sleep_us(us);
}

#endif // _DELAY_H_
