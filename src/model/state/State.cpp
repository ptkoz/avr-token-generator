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

#include "Arduino.h"
#include "State.h"

using namespace model::state;

State::State(): currentState(IDLE), lastStateChange(millis()) { }
State::~State() { }

bool State::isTimedOut() const {
	unsigned long age = millis() - lastStateChange;
	switch(currentState) {
		case IDLE:
			// CPU goes to sleep when IDLE state is timed out.
			return age > 10000;

		case TOKEN_REQUESTED:
			// Progress bar must be completed on this timeout.
			return age > 1900;

		case AWAITING_CONFIRMATION:
			// How many seconds after progress bar is completed
			// shall we wait for token on the serial port?
			return age > 1000;

		case TOKEN_READY:
		case REQUEST_TIMEOUT:
			// Success / failure message will be displayed as long
			// as this state is not timed out.
			return age > 10000;

		default:
			// Just in case. Should not happen.
			return age > 1000;

	}
}

State & State::operator =(const ApplicationState newState) {
	currentState = newState; // Change state.
	lastStateChange = millis(); // Record change timestamp.
	return *this;
}

bool State::operator ==(const ApplicationState comparedState) const {
	return comparedState == currentState;
}

bool model::state::operator ==(const ApplicationState stateA, const State & stateB) {
	return stateB == stateA; // Pass to the class' == operator.
}
