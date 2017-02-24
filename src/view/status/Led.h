/*
 * StatusLed.h
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 *
 * This class controlls behavior of the status LED
 * attached to display.
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
