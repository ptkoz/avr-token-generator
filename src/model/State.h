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
	// state type definition
	typedef enum { IDLE = 0, TOKEN_READY, REQUEST_TIMEOUT, TOKEN_REQUESTED = 100, AWAITING_TOKEN } state;

	class State {
		public:
			State();
			~State();

			// are we during new token request?
			bool isProcessingRequest() const { return currentState >= TOKEN_REQUESTED; }

			// is current state timed out?
			bool isTimedOut() const;

			// set the new state
			State & operator =(const state newState);
			bool operator==(const state state) const;
		private:
			state currentState;
			unsigned long lastStateChange;

	};

	bool operator ==(const state stateA, const State & stateB);
}}

#endif /* SRC_MODEL_STATE_H_ */
