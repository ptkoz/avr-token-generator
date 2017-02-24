#include "Buzzer.h"
using namespace view::status::buzzer;

Buzzer::Buzzer(const char pin): output(pin), beepsToPlay(0), nextMessage(IDLE) { }
Buzzer::~Buzzer() { }

void Buzzer::beep(const Message msg) {
	nextMessage = msg;
}

void Buzzer::update() {
	// beep interval is calculated for each message
	static unsigned short beepInterval = 0;

	// check if we can begin playing next message
	if(0 == beepsToPlay && IDLE != nextMessage && output.getMillisFromLastStateChange() > MESSAGE_INTERVAL) {
		beepsToPlay = nextMessage;
		nextMessage = IDLE;
		beepInterval = MESSAGE_DURATION / beepsToPlay;
	}

	// if there are some beeps to play left, let's play them
	if(beepsToPlay > 0 && output.getMillisFromLastStateChange() > beepInterval) {
		if(output.getCurrentState()) {
			// buzzer has completed beep cycle, decrement number of beeps to play
			beepsToPlay--;
		}

		output.toggle();
	}
}
