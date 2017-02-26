/*
 * Copyright (C) 2017 patryk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIG_H
#define CONFIG_H

/*
 * Here comes the Arduino pins configuration
 */
// Request token button - must be interruptable pin.
#define PIN_BUTTON 2
// Status LED.
#define PIN_SLED 13
// Message buzzer
#define PIN_BUZZER 4

// LCD pins.
#define PIN_LCD_BACKLIGHT 5
#define PIN_LCD_RS 6
#define PIN_LCD_RW 7
#define PIN_LCD_EN 8
#define PIN_LCD_D0 9
#define PIN_LCD_D1 10
#define PIN_LCD_D2 11
#define PIN_LCD_D3 12

// Uplugged analog pin prividing some entropy to PRNG
#define PIN_ANALOG_UNPLUGGED 0

// Token config.
#define TOKEN_LENGTH 6

#endif /* CONFIG_H */

