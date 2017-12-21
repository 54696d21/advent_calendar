# advent_calendar

This is a simple advent calendar that displays the current date (just the day)
by lighting up as many leds accordingly.

The ESP8266 is used to get the current date (and time) via NTP.

I use it with a led ring consisting of 24 WS2812.
The comments are partly in German as I didn't change it yet.

Currently there are no checks implemented to determine wether it is december or not. So it will work in any month.
It can also be easily modified to work as a regular calendar by using more leds (at least 31) and changing the
defintion of "PIXELS" in the code.

The code was tested in PlatformIO but should also work in the Arduino IDE just as well.
