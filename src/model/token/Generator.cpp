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

#include "Generator.h"
using namespace model::token;

Generator::Generator(const byte unpluggedAnalogPin): 
	randomProvider(unpluggedAnalogPin),
	tokenLength(0),
	generatedChars(0),
	token(NULL)
{ }


Generator::~Generator() {
	if(token) delete [] token;
}

void Generator::start(const byte newTokenLength) {  
	tokenLength = newTokenLength;
	generatedChars = 0;
	
	if(token) delete [] token;
	token = new char[tokenLength+1]; // + terminating NULL character
	token[tokenLength] = 0;
}

void Generator::update() {
	if(tokenLength > generatedChars) {
		// generate char with value between 48 - 57 (ASCII '0-9') or 65 - 90 (ASCII uppercase letters)
		char c = randomProvider.randomNumber(48, 83);
		if(c > 57) c += 8;
		
		// Ignore chars from set (0, O, 1, I) as they look to similar
		if(48 != c && 79 != c && 49 != c && 73 != c) {
			token[generatedChars++] = c;
		}
	}
}