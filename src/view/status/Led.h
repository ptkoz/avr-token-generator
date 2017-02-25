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

#ifndef SRC_VIEW_STATUS_LED_H_
#define SRC_VIEW_STATUS_LED_H_

#include "../../tool/pin/digital/Output.h"

namespace view { namespace status { namespace led {
	// handy namespace constants
	const unsigned short BLINKING_INTERVAL = 100;

	// class declaration
	class Led {
		public:
			Led(const char pin);
			~Led();

			// component state management
			void enable() { enabled = true; }
			void disable() { enabled = false; }

			// API for controller loop
			void update();

		private:
			// output pin
			tool::pin::digital::Output output;

			// are we blinking or not?
			bool enabled;
	};
}}}

#endif /* SRC_VIEW_STATUS_LED_H_ */
