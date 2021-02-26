# RGB LED With Attiny13A

## Intro

- Pet project in covid 2021 to light up **[Virgin Mary]([Maria – Wikipedia tiếng Việt](https://vi.wikipedia.org/wiki/Maria))** crystal statue

- Arduino Uno as an ISP programmer. Thanks to [Arduino/Attiny13A.ISP.Arduino.Programmer at master · spiderock98/Arduino (github.com)](https://github.com/spiderock98/Arduino/tree/master/Attiny13A.ISP.Arduino.Programmer)

- Vanilla AVR-GCC via PlatformIO

- General Configuration
  
  - Disable ADC module for low power consumption
  
  - Internal 1.2MHz + PWM prescale DIV_64 using timer0
  
  - Disable BOD
  
  - Using WDT Timer Interrupt with `millis()` to set duration parameter for `LED_MODx(uint32_t duration_ms)` function (Attiny13 just got only 1 timer0)
  
  - 1 [led rgb]([LED RGB 1210 Dán SMD Trong Suốt, Size 3.2x2.5mm, điện áp 1.8~2... (thegioiic.com)](https://www.thegioiic.com/products/led-rgb-1210-dan-smd-trong-suot)) connect to push-pull PB0 output
  
  - [CMOS CR2032]([Pin CMOS CR2032 ra jack cắm (icdayroi.com)](https://icdayroi.com/pin-cmos-cr2032-ra-jack-cam)) battery for whole microcontroller and led

## Gallery

## To-Do

- [ ] Test power up time (hopefully upto 7 hours if i calculate correctly 😊)

- [ ] Test charge circuit












