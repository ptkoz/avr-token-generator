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

#include "Buzzer.h"
using namespace view::status::buzzer;

Buzzer::Buzzer(const char pin): output(pin), beepsToPlay(0), nextMessage(IDLE) { }
Buzzer::~Buzzer() { }

void Buzzer::beep(const Message msg) {
	nextMessage = msg;
}

void Buzzer::update() {
	// Beep interval is calculated for each message.
	static unsigned short beepInterval = 0;

	// Check if we can begin playing next message.
	if(0 == beepsToPlay && IDLE != nextMessage && output.getMillisFromLastStateChange() > MESSAGE_INTERVAL) {
		beepsToPlay = nextMessage;
		nextMessage = IDLE;
		beepInterval = MESSAGE_DURATION / beepsToPlay;
	}

	// If there are some beeps to play left, let's play them.
	if(beepsToPlay > 0 && output.getMillisFromLastStateChange() > beepInterval) {
		if(output.getCurrentState()) {
			// Buzzer has completed beep cycle, decrement number of beeps to play.
			beepsToPlay--;
		}

		output.toggle();
	}
}
