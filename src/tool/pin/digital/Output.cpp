#include "Arduino.h"
#include "Output.h"

using namespace tool::pin::digital;

Output::Output(const char pin):
	Pin(pin),
	lastStateChange(0)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

Output::~Output() {
	digitalWrite(pin, LOW);
}

void Output::write(bool state) {
	lastStateChange = millis();
	digitalWrite(pin, state);
}

void Output::enable() {
	write(true);
}

void Output::disable() {
	write(false);
}

void Output::toggle() {
	write(!getCurrentState());
}

unsigned long Output::getMillisFromLastStateChange() const {
	return millis() - lastStateChange;
}
