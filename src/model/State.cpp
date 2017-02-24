/*
 * State.cpp
 *
 *  Created on: 21.02.2017
 *      Author: patryk
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
			return age > 10000;

		case TOKEN_REQUESTED:
			return age > 1900;

		case AWAITING_TOKEN:
			return age > 1000;

		case TOKEN_READY:
		case REQUEST_TIMEOUT:
			return age > 10000;

		default:
			return age > 1000;

	}
}

State & State::operator =(const state newState) {
	currentState = newState;
	lastStateChange = millis();
	return *this;
}

bool State::operator ==(const state comparedState) const {
	return comparedState == currentState;
}

bool model::state::operator ==(const state stateA, const State & stateB) {
	return stateB == stateA;
}
