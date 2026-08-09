#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>


enum {
    GPIO_MODE_IN = 0,
    GPIO_MODE_OUT = 1,
};

enum {
    GPIO_FUNCTION_SPI = 1,
    GPIO_FUNCTION_PWM = 4,
};


void GPIO_Write(uint16_t pin, uint8_t value);
uint8_t GPIO_Read(uint16_t pin);
void GPIO_Mode(uint16_t pin, uint16_t mode);
void GPIO_Set_Function(uint16_t pin, uint_fast16_t func);

#endif // _GPIO_H_
