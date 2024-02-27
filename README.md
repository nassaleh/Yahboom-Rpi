# Yahboom-Rpi

## What is Yahboom?
http://www.yahboom.net/study/RGB_COOLING_HAT

The Yahboom RGB Cooling hat is a hat designed for Raspberry Pi 4B/3B+/3B that has the following features:
- PWM fan controlled via I2C
- 3x RGB LEDs controlled via I2C
- An OLED Display

## What is this code
This is my own implementation of the sample code provided by Yahboom that does not depend on WiringPi. 
Given that WiringPi is deprecated and did not support 64 bit, I have decided to make my own library.

Using [Linux's I2C Interface](https://www.kernel.org/doc/Documentation/i2c/dev-interface)

This is a library to be used with a Raspberry Pi 4 and a Yahboom RGB hat.


# TODO
- [x] Fan control
- [x] LED Control
- [ ] Monitor control
- [ ] Command line argument support
- [ ] Kernel level driver to be able to use /dev/fan directly.
