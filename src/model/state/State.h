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

#ifndef SRC_MODEL_STATE_H_
#define SRC_MODEL_STATE_H_

namespace model { namespace state {
	/*
	 * Application state types:
	 * 
	 * -- IDLE --
	 * Nothing is happening, display is cleared and powered
	 * off and status LED is disabled.
	 * 
	 * -- TOKEN_READY --
	 * Token has been successfully generated and is currently
	 * displayed on the LCD screen. Status LED is disabled.
	 * 
	 * -- REQUEST_TIMEOUT --
	 * Token could not be generated. Timeout message is currently
	 * displayed on the LCD screen. Status LED is disabled.
	 * 
	 * -- TOKEN_REQUESTED --
	 * User has requested for the token. Progres bar is
	 * displayed on the LCD screen and the status LED is
	 * blinking.
	 * 
	 * -- AWAITING_TOKEN --
	 * Progress bar has reached it's endpoint. We can
	 * now receive token and show it to the user.
	 * 
	 * Please note that following enum is order-sensitive. State
	 * values greater or equal TOKEN_REQUESTED (100) are "busy"
	 * states in which new token requests are ignored.
	 */ 
	typedef enum { IDLE = 0, TOKEN_READY, REQUEST_TIMEOUT, TOKEN_REQUESTED = 100, AWAITING_TOKEN } state;

	/*
	 * Class that controlls the application state.
	 */
	class State {
		public:
			State();
			~State();

			// Are we during new token request?
			bool isProcessingRequest() const { return currentState >= TOKEN_REQUESTED; }

			// Is current state timed out?
			bool isTimedOut() const;

			// Set the new state.
			State & operator =(const state newState);
			
			// Compare current state.
			bool operator==(const state state) const;
		private:
			state currentState;
			unsigned long lastStateChange;

	};

	// Allow state comparison with constant on the left side.
	bool operator ==(const state stateA, const State & stateB);
}}

#endif /* SRC_MODEL_STATE_H_ */
