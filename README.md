# Token generator for AVR (ATmega) platform
## Overview
AVR token generator is simple application for embedded devices based on AVR (ATmega) micro controller. The idea behind is to provide physical interface (button, screen) in physical location (eg. home) to authorize users in some IT environments. Generated tokens are sent to the controlling unit via standard serial port.

Please note that the whole authorization depends on user having physical access to the device. For example if you have guest WiFi in your home with token-guarded captive portal, you may place the device next to the router and connect it via USB. Everyone who has access to your home should probably also be able to authorize in Guest WiFi (and it's actually what I use the device for).

## API specification

There are several message types sent through serial port to the controlling unit. Each message is followed by CRLF char sequence.

* Messages starting with "LOG:"

Those are debug messages, sent from time to time to have some basic idea about the device state. You may safely ignore them or store them in the log file.

* Messages starting with "TKN:"

This is how new tokens are sent to the controlling unit. You should reply with simple "OK" followed by CRLF to inform device that everything is OK and user may authorize himself with the token.

## Credits

This software was originally designed for Arduino Uno platform and - for simplicity - is built using slightly modified Arduino code library. Although project is managed in Netbeans IDE with appropriate Makefiles, you may still need Arduino IDE to provide valid toolchain and libraries.