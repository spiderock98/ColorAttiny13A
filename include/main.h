#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

enum pwm_mode
{
    NORMAL,
    CTC,
    FAST_PWM,
    PHASE_CORRECT
};

enum pwm_freq
{
    DIV_1 = _BV(CS00),
    DIV_8 = _BV(CS01),
    DIV_64 = _BV(CS01) | _BV(CS00),
    DIV_256 = _BV(CS02),
    DIV_1024 = _BV(CS02) | _BV(CS00)
};

void RGB_MODE1(uint32_t duration_ms);