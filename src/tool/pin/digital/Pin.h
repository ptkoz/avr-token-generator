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

#ifndef TOOL_PIN_DIGITAL_PIN_H_
#define TOOL_PIN_DIGITAL_PIN_H_

namespace tool { namespace pin { namespace digital {
	/*
	 * Class for reading digital PIN state 
	 * in object oriented manner.
	 */
	class Pin {
		public:
			Pin(const char pin);
			virtual ~Pin();

			// What is the current state?
			virtual bool getCurrentState() const;
		protected:
			// Digital ouput pin to use.
			const char pin;
	};
}}}

#endif /* TOOL_PIN_DIGITAL_PIN_H_ */
