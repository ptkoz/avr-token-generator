/*
 * Buzzer.h
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 *
 *  Buzzer messaging service. Comunicates with user
 *  by simple sounds.
 */

#ifndef SRC_VIEW_STATUS_BUZZER_H_
#define SRC_VIEW_STATUS_BUZZER_H_

#include "../../tool/pin/digital/Output.h"

namespace view { namespace status { namespace buzzer {
	// handy namespace constants
	const unsigned short MESSAGE_DURATION = 150;
	const unsigned short MESSAGE_INTERVAL = 300;

	// type represents number of beeps for each message
	typedef enum { IDLE = 0, SUCCESS = 1, BUSY = 2, FAILURE = 3 } Message;

	// class declaration
	class Buzzer {
		public:
			Buzzer(const char pin);
			~Buzzer();

			// beep out the message
			void beep(Message msg);

			// API for controller loop
			void update();
		private:
			tool::pin::digital::Output output;

			// how many beeps to play in current message?
			unsigned char beepsToPlay;

			 // next message in queue
			Message nextMessage;
	};
}}}

#endif /* SRC_VIEW_STATUS_BUZZER_H_ */
