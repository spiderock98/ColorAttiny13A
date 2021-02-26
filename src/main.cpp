#include "main.h"
#include <Arduino.h>

void pwm_set_duty(uint8_t duty)
{
    OCR0A = duty;
}
void init_PWM(pwm_freq prescaler, pwm_mode mode)
{
    TCCR0B = TCCR0B & ~_BV(CS02) & ~_BV(CS01) & ~_BV(CS00) | prescaler;

    switch (mode)
    {
    case CTC:
        TCCR0A |= _BV(COM0A0); // toggle
        // TCCR0A |= _BV(COM0A1); // Clear
        TCCR0A |= _BV(WGM01); // mode 2
        pwm_set_duty(50);
        //        TCCR0A = TCCR0A | (1 << COM0A1) & ~(1 << COM0A0); // Clear OC0A on Compare Match
        break;
    case FAST_PWM:
        // TCCR0A |= _BV(COM0A0); // just use toggle with mode 7 fast pwm and 2 CTC
        TCCR0A |= _BV(COM0A1); // Clear OC0A on Compare Match
        // TCCR0B |= _BV(WGM02);              // mode 7 Fast PWM cannot run as pwm
        TCCR0A |= _BV(WGM01) | _BV(WGM00); // mode 3 Fast PWM
        break;

    default:
        break;
    }
}
void init_IO()
{
    DDRB |= _BV(DDB0); // set PWM pin as OUTPUT
}

int main()
{
    PRR |= _BV(PRADC); // shut down Timer/Counter0 module and ADC module

    init_IO();
    init_PWM(DIV_64, FAST_PWM);

    // TIMSK0 |= _BV(OCIE0A); // enable interrupt
    // sei();                 // enable global interrupts

    RGB_MODE1(10000);
    while (1)
    {
    }
}
void RGB_MODE1(uint32_t duration_ms)
{
    static uint32_t now_mode1 = millis();
    for (uint8_t cntDuty = 0; cntDuty < 255; ++cntDuty)
    {
        pwm_set_duty(cntDuty);
        _delay_ms(10);
    }
    for (uint8_t cntDuty = 255; --cntDuty;)
    {
        pwm_set_duty(cntDuty);
        _delay_ms(10);
    }
    if (millis() - now_mode1 > duration_ms)
        return;
    else
        RGB_MODE1(duration_ms);
}

// volatile bool flagToggle = 1;
// ISR(TIM0_COMPA_vect)
// {
//     if (flagToggle)
//         pwm_set_duty(200);
//     else
//         pwm_set_duty(100);
//     flagToggle = !flagToggle;
// }
