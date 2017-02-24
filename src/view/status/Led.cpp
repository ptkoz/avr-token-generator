#include "Led.h"
using namespace view::status::led;

Led::Led(char pin): output(pin), enabled(false) { }
Led::~Led() { }

void Led::update() {
	if(enabled) {
		/*
		 * If component is enabled, we shall blink the status LED.
		 * Check last tick time and change output of needed
		 */
		if(output.getMillisFromLastStateChange() > BLINKING_INTERVAL) {
			output.toggle();
		}
	} else if(output.getCurrentState()) {
		/**
		 * Component is disabled, but led is still enabled.
		 * Let's disable it.
		 */
		output.disable();
	}
}
