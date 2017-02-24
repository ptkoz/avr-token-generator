/**
 * Created on: 21.02.2017
 *      Author: patryk
 *
 * Class fot reading digital pin state.
 */

#ifndef TOOL_PIN_DIGITAL_PIN_H_
#define TOOL_PIN_DIGITAL_PIN_H_

namespace tool { namespace pin { namespace digital {
	class Pin {
		public:
			Pin(const char pin);
			virtual ~Pin();

			// what is the current state?
			virtual bool getCurrentState() const;
		protected:
			// digital ouput pin to use
			const char pin;
	};
}}}

#endif /* TOOL_PIN_DIGITAL_PIN_H_ */
