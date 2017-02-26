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

#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>

namespace model { namespace prng {
/*
 * PRNG utilizing secure concept presented by Aaron Ardiri.
 * See more on his blog post:
 * <http://ardiri.com/blog/secure_number_generator_for_the_arduino>
 */
class Provider {
	public:
		Provider(const unsigned char unpluggedAnalogPin);
		~Provider();
		
		// Get a random number between min and max-1
		long randomNumber(long min, long max);
	private:
		// Provide random data using analog input.
		byte randomBitFromAnalog();
		byte randomByteFromAnalog();
		word randomWordFromAnalog();
		
		// How many bytes were generated using current seed?
		int numbersGenerated;
		
		// How many bytes are allowed using current seed?
		int numbersAllowed;
		
		// Pin number.
		const unsigned char unpluggedAnalogPin;
};

}}

#endif /* RANDOM_H */

