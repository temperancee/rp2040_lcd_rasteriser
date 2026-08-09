#include "GPIO.h"
#include <hardware/gpio.h>


void GPIO_Write(uint16_t pin, uint8_t value)
{
    gpio_put(pin, value);
}

uint8_t GPIO_Read(uint16_t pin)
{
    return gpio_get(pin);
}

void GPIO_Mode(uint16_t pin, uint16_t mode)
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

void GPIO_Set_Function(uint16_t pin, uint_fast16_t func)
{
    gpio_set_function(pin, func);
}
