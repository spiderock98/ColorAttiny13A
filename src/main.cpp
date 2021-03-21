#include "main.h"
#include <Arduino.h>

void pwm_set_duty(uint8_t duty, PinPWM selectPin)
{
    if (selectPin == MATCH_A)
        OCR0A = duty;
    else if (selectPin == MATCH_B)
        OCR0B = duty;
}
void init_PWM(pwm_freq prescaler, pwm_mode mode, PinPWM selectPin)
{
    TCCR0B = TCCR0B & ~_BV(CS02) & ~_BV(CS01) & ~_BV(CS00) | prescaler;

    switch (mode)
    {
    case CTC:
        TCCR0A |= _BV(COM0A0); // toggle
        // TCCR0A |= _BV(COM0A1); // Clear
        TCCR0A |= _BV(WGM01); // mode 2
        pwm_set_duty(50, MATCH_A);
        pwm_set_duty(50, MATCH_B);
        //        TCCR0A = TCCR0A | (1 << COM0A1) & ~(1 << COM0A0); // Clear OC0A on Compare Match
        break;
    case FAST_PWM:
        // TCCR0A |= _BV(COM0A0); // just use toggle with mode 7 fast pwm and 2 CTC
        // TCCR0A |= _BV(COM0A1); // Clear OC0A on Compare Match A Mode
        // TCCR0A |= _BV(COM0B1); // Clear OC0B on Compare Match B Mode
        TCCR0A |= (selectPin == MATCH_A) ? _BV(COM0A1) : _BV(COM0B1);
        // TCCR0B |= _BV(WGM02);              // mode 7 Fast PWM cannot run as pwm
        TCCR0A |= _BV(WGM01) | _BV(WGM00); // mode 3 Fast PWM
        break;

    default:
        break;
    }
}
void init_IO()
{
    DDRB |= _BV(DDB0); // set PWM pin PB0 as match A OUTPUT
    DDRB |= _BV(DDB1); // set PWM pin PB1 as match B OUTPUT
    DDRB |= _BV(DDB2); // set PB2 as  OUTPUT
}

int main()
{
    PRR |= _BV(PRADC); // shut down Timer/Counter0 module and ADC module

    init_IO();
    init_PWM(DIV_64, FAST_PWM, MATCH_A);
    init_PWM(DIV_64, FAST_PWM, MATCH_B);

    // TIMSK0 |= _BV(OCIE0A); // enable interrupt
    // sei();                 // enable global interrupts

    RGB_MODE1();
    while (1)
    {
    }
}

void RGB_MODE1(int32_t duration_ms = -1)
{
    static int32_t now_mode1 = millis();
    PORTB |= _BV(PORTB2);
    for (uint8_t cntDuty = 0; cntDuty < 255; ++cntDuty)
    {
        pwm_set_duty(cntDuty, MATCH_A);
        // pwm_set_duty(255 - cntDuty, MATCH_B);
        _delay_ms(10);
    }

    PORTB &= ~_BV(PORTB2);
    for (uint8_t cntDuty = 255; --cntDuty;)
    {
        pwm_set_duty(cntDuty, MATCH_A);
        // pwm_set_duty(255 - cntDuty, MATCH_B);
        _delay_ms(10);
    }

    if (duration_ms == -1)
    {
        // to infinity and beyond
        RGB_MODE1(-1);
    }
    else if (millis() - now_mode1 > duration_ms)
        return;
    else
        RGB_MODE1(duration_ms);
}