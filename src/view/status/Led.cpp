/*
 * Copyright (C) 2017 Patryk Kozłowski
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

#include "Led.h"
using namespace view::status::led;

Led::Led(char pin): output(pin), enabled(false) { }
Led::~Led() { }

void Led::update() {
	if(enabled) {
		/*
		 * If component is enabled, we shall blink the status LED.
		 * Check last tick time and change output of needed
		 */
		if(output.getMillisFromLastStateChange() > BLINKING_INTERVAL) {
			output.toggle();
		}
	} else if(output.getCurrentState()) {
		/**
		 * Component is disabled, but led is still enabled.
		 * Let's disable it.
		 */
		output.disable();
	}
}
