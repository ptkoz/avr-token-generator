# Token generator for AVR (ATmega) platform
## Overview
AVR token generator is simple application for embedded devices based on AVR (ATmega) micro controller. The idea behind is to provide physical interface (button, screen) in physical location (eg. home) to authorize users in some IT environments. Generated tokens are sent to the controlling unit via standard serial port.

Please note that the whole authorization depends on user having physical access to the device. For example if you have guest WiFi in your home with token-guarded captive portal, you may place the device next to the router and connect it via USB. Everyone who has access to the device in your home should probably also be able to authorize in Guest WiFi (and it's actually what I'm using it for).

## API specification

There are several message types sent through serial port to the controlling unit. Each message is followed by `LF` char sequence.

* Messages starting with `"LOG:"`

Those are debug messages, sent from time to time to provide some basic device status. You may safely ignore them or - if you want - store them in some log file.

* Messages starting with `"TKN:"`

This is how new tokens are sent to the controlling unit. You should reply with simple `"OK"` followed by `LF` (warning: NOT `CRLF`) to inform device that everything is OK and user may authorize himself with the token. If you reply with anything different than `"OK\n"`, eg. `"FAIL\n"`, the token will be discarded and another token will be generated. This process will continue up to the timeout defined in application.

## Credits

This software was originally designed for Arduino Uno platform and - for simplicity - is built using slightly modified Arduino code library. Although project is managed in Netbeans IDE with appropriate Makefiles, you may still need Arduino IDE to provide proper AVR toolchain and libraries.