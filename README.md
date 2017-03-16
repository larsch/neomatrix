# NeoMatrix

Source code for 24x24 neopixel (WS2812b) matrix display

Runs various demo effects and pixel art (Metaballs, fire effect, The
Matrix simulator, etc.)

## Compiling for ESP8266

Compile the `src\neomatrix.ino` sketch in the Arduino IDE for the
ESP8266. Use
the [Arduino core for ESP8266](https://github.com/esp8266/Arduino).

## Compiling for PC

The source includes a simulator based on SDL2 than can be run on a
PC. With SDL2 libraries installed, the Makefile can be generated using
CMake:

```
mkdir build
cd build
cmake ../sim
make
./matrix
```

## Credits

Copyright (C) 2016-2017 Lars Christensen

This project is licensed under the terms of the MIT license.

WS2812 I2S driver based on code originally by Charles Lohr. See
https://github.com/cnlohr/esp8266ws2812i2s.
