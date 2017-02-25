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
	// When status LED is enabled, how often should it blink?
	const unsigned short BLINKING_INTERVAL = 100;

	/*
	 * Class controlling the status LED. Status
	 * LES shall blink when device is busy.
	 */
	class Led {
		public:
			Led(const char pin);
			~Led();

			// Component state management.
			void enable() { enabled = true; }
			void disable() { enabled = false; }

			// API for controller loop.
			void update();

		private:
			// Output pin.
			tool::pin::digital::Output output;

			// Are we blinking in blinking mode or not?
			bool enabled;
	};
}}}

#endif /* SRC_VIEW_STATUS_LED_H_ */
