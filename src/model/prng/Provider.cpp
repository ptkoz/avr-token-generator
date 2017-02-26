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

#include "Provider.h"

using namespace model::prng;

// Initial values allow seed to be generated on first random() run.
Provider::Provider(const unsigned char unpluggedAnalogPin): numbersGenerated(0), numbersAllowed(1), unpluggedAnalogPin(unpluggedAnalogPin) { }
Provider::~Provider() { }

long Provider::randomNumber(const long min, const long max) {
	if(0 == (numbersGenerated++ % numbersAllowed)) {
		// generate new seed
		randomSeed(randomWordFromAnalog());
		// use the same seed a maximum of 64 times
		numbersAllowed = (randomByteFromAnalog() >> 2) + 1;
	}
	
	return random(min, max);
}

byte Provider::randomBitFromAnalog() {
	for(;;) {
		byte a = (analogRead(0) & 1) | ((analogRead(0) & 1) << 1);
		if (a == 1) return 0;
		if (a == 2) return 1;
		// otherwise, keep looking
	}
}

byte Provider::randomByteFromAnalog() {
	byte output = 0;
	// random byte has 8 random bits
	for(byte i = 0; i < 8; i++) {
		output |= (randomBitFromAnalog() << i);
	}
	
	return output;
}


word Provider::randomWordFromAnalog() {
	word output = 0;
	
	// get as many random bytes as there are in word
	for(byte byteNumber = 0; byteNumber < sizeof(word); byteNumber++) {
		output |= (randomByteFromAnalog() << (byteNumber * 8));
	}
	
	return output;
}