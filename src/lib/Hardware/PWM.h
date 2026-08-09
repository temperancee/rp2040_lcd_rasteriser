#ifndef _PWM_H_
#define _PWM_H_

#include <stdbool.h>
#include <stdint.h>
#include <hardware/pwm.h>

enum {
    PWM_CHANNEL_A = PWM_CHAN_A,
    PWM_CHANNEL_B = PWM_CHAN_B
};

static inline uint32_t PWM_GPIO_to_Slice_Num(uint32_t pin)
{
    return pwm_gpio_to_slice_num(pin);
}

static inline void PWM_Set_Wrap(uint32_t slice_num, uint16_t wrap)
{
    pwm_set_wrap(slice_num, wrap);
}

static inline void PWM_Set_Chan_Level(uint32_t slice_num, uint32_t chan, uint16_t level)
{
    pwm_set_chan_level(slice_num, chan, level);
}

static inline void PWM_Set_Clkdiv(uint32_t slice_num, uint8_t divider)
{
    pwm_set_clkdiv(slice_num, (float) divider);
}

static inline void PWM_Set_Enabled(uint32_t slice_num, bool enabled)
{
    pwm_set_enabled(slice_num, enabled);
}

#endif // _PWM_H_
