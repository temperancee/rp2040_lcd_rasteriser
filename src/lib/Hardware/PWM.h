#ifndef _PWM_H_
#define _PWM_H_

#include <stdbool.h>
#include <stdint.h>
#include <hardware/pwm.h>

// Mimic PWM_CHAN_A/B from the SDK
enum {
    PWM_CHANNEL_A = 0, 
    PWM_CHANNEL_B = 1
};

uint32_t PWM_GPIO_to_Slice_Num(uint32_t pin);
void PWM_Set_Wrap(uint32_t slice_num, uint16_t wrap);
void PWM_Set_Chan_Level(uint32_t slice_num, uint32_t chan, uint16_t level);
void PWM_Set_Clkdiv_Int(uint32_t slice_num, uint8_t divider);
void PWM_Set_Enabled(uint32_t slice_num, bool enabled);

#endif // _PWM_H_
