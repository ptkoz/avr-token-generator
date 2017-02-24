/*
 * Created on: 21.02.2017
 *      Author: patryk
 *
 *  Class fot controlled output of single digital pin.
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
