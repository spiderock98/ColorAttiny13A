# RGB LED With Attiny13A

## Intro

- Pet project in covid 2021 to light up **[Virgin Mary](https://vi.wikipedia.org/wiki/Maria)** crystal statue

- Arduino Uno as an ISP programmer. Thanks to [Arduino/Attiny13A.ISP.Arduino.Programmer at master · spiderock98/Arduino (github.com)](https://github.com/spiderock98/Arduino/tree/master/Attiny13A.ISP.Arduino.Programmer)

- Vanilla AVR-GCC via PlatformIO

- General Configuration

  - Disable ADC module for low power consumption

  - Internal 1.2MHz + PWM prescale DIV_64 using timer0

  - Disable BOD

  - Using WDT Timer Interrupt with `millis()` to set duration parameter for `LED_MODx(uint32_t duration_ms)` function (Attiny13 just got only 1 timer0)

  - [Led RGB common anode](https://www.thegioiic.com/products/led-rgb-1210-dan-smd-trong-suot) connect to push-pull PB0 output

  - [Lipo 500mAh 3.7v](https://icdayroi.com/pin-lipo-500mah-3-7v) battery for both microcontroller and led

## Specs

|               Parameter                |            Value             |
| :------------------------------------: | :--------------------------: |
|              LED Voltage               |         2.6 V / pin          |
|              LED Current               |         27 mA / pin          |
|                Resistor                |      4x 10 Ohm = 40 Ohm      |
| MCU Current Consumption in Active Mode |            0.5 mA            |
|               PWM Output               | PB0 and PB1 (out of PWM pin) |

<img src="resource\docs\pinout.png" title="" alt="" data-align="center">
<img src="resource\docs\IV-curves-all-colours.png" title="" alt="" data-align="center">
<img src="resource\docs\current_consumption.png" title="" alt="" data-align="center">

## Gallery

<img src="resource\img\IMG_20210321_201045.jpg" title="" alt="" width="45%" data-align="center">
<img src="resource\img\IMG_20210321_201058.jpg" title="" alt="" width="45%" data-align="center">
<img src="resource\img\IMG_20210321_201135.jpg" title="" alt="" width="45%" data-align="center">
<img src="resource\img\IMG_20210321_201204.jpg" title="" alt="" data-align="center">
<img src="resource\img\IMG_20210321_201333.jpg" title="" alt="" data-align="center">

## To-Do

- [x] Test power up time (hopefully upto 17 hours if i calculate correctly 😊)

- [ ] Test charge circuit

- [ ] Remake version 2
