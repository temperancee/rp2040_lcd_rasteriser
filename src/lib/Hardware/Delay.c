#include "Delay.h"
#include <pico/time.h>

void GDB_Fix(void)
{
    timer_hw->dbgpause = 0;
}

void Delay_ms(uint32_t xms)
{
#ifdef NDEBUG
    sleep_ms(xms);
#else
    // If this is a debug build, use the blocking sleep function,
    // so we can step through/over it without GDB hanging
    busy_wait_ms(xms);
#endif
}

void Delay_us(uint32_t xus)
{
#ifdef NDEBUG
    sleep_us(xus);
#else
    // If this is a debug build, use the blocking sleep function,
    // so we can step through/over it without GDB hanging
    busy_wait_us(xus);
#endif
}
