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

#ifndef TOOL_PIN_DIGITAL_OUTPUT_H_
#define TOOL_PIN_DIGITAL_OUTPUT_H_

#include "Pin.h"

namespace tool { namespace pin { namespace digital {
	class Output : public Pin {
		public:
			Output(const char pin);
			~Output();

			// control output
			void enable();
			void disable();
			void toggle();

			// how many milliseconds elapsed from last state change?
			unsigned long getMillisFromLastStateChange() const;
		private:
			unsigned long lastStateChange;

			// change the state
			void write(bool state);
	};
}}}

#endif /* TOOL_PIN_DIGITAL_OUTPUT_H_ */
