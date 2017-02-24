/*
 * State.h
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 *
 *  Class handling current model state.
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
