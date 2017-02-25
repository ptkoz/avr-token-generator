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

#include "Arduino.h"
#include "Output.h"

using namespace tool::pin::digital;

Output::Output(const char pin):
	Pin(pin),
	lastStateChange(0)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

Output::~Output() {
	digitalWrite(pin, LOW);
}

void Output::write(bool state) {
	lastStateChange = millis();
	digitalWrite(pin, state);
}

void Output::enable() {
	write(true);
}

void Output::disable() {
	write(false);
}

void Output::toggle() {
	write(!getCurrentState());
}

unsigned long Output::getMillisFromLastStateChange() const {
	return millis() - lastStateChange;
}
