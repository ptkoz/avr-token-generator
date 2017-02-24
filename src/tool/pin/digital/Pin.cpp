#include "Arduino.h"
#include "Pin.h"

using namespace tool::pin::digital;

Pin::Pin(const char pin): pin(pin) { }
Pin::~Pin() { }

bool Pin::getCurrentState() const {
	return digitalRead(pin);
}
