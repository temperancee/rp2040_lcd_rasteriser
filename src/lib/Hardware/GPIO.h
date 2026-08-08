#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include <hardware/gpio.h>


enum {
    GPIO_MODE_IN = GPIO_IN,
    GPIO_MODE_OUT = GPIO_OUT,
};

enum {
    GPIO_FUNCTION_SPI = 1,
    GPIO_FUNCTION_PWM = 4,
};


static inline void GPIO_Write(uint16_t pin, uint8_t value)
{
    gpio_put(pin, value);
}

static inline uint8_t GPIO_Read(uint16_t pin)
{
    return gpio_get(pin);
}

static inline void GPIO_Mode(uint16_t pin, uint16_t mode)
{
    gpio_init(pin);
    if (mode == GPIO_MODE_IN)
    {
        gpio_set_dir(pin, GPIO_IN);
    }
    else
    {
        gpio_set_dir(pin, GPIO_OUT);
    }
}

static inline void GPIO_Set_Function(uint16_t pin, uint_fast16_t func)
{
    gpio_set_function(pin, func);
}

#endif // _GPIO_H_
