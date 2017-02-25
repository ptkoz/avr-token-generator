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
