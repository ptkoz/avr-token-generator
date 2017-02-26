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
#ifndef GENERATOR_H
#define GENERATOR_H

#include <Arduino.h>
#include "../prng/Provider.h"

namespace model { namespace token {
	
/*
 * Class used for generating tokens.
 */
class Generator {
	public:
		Generator(const byte unpluggedAnalogPin);
		~Generator();
		
		// Start generating new token using specified random::Provider.
		void start(const byte tokenLength);
		
		// Is generated token ready?
		bool isReady() { return tokenLength == generatedChars; }
		
		// API for main controller loop.
		void update();
		
		// Remember to copy token to some other place in memory
		// if you're generating multiple tokens, as this value
		// is going to be overwriten on next generate() call.
		const char * getToken() { return token; }
	private:
		// Currently used random provider.
		prng::Provider randomProvider;
		
		// How many chars in token?
		byte tokenLength;
		
		// How many chars already generated?
		byte generatedChars;
		
		// Token buffer.
		char * token;

};

}}

#endif /* GENERATOR_H */

