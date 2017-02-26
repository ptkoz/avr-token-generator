/*
 * Copyright (C) 2017 patryk
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

#ifndef API_H
#define API_H

#include <Arduino.h>

namespace tool { namespace rs232 {

	/*
	 * Token verification state types:
	 * 
	 * -- NO_TOKEN --
	 * There is no token to verify.
	 * 
	 * -- VERIFICATION_WAITING --
	 * Token was sent to controlling unit, we're awaiting response.
	 * 
	 * -- VERIFICATION_OK --
	 * Token was successfully verified and may be displayed to user
	 * as valid.
	 * 
	 * -- VERIFICATION_FAILED --
	 * Controlling unit refused to accept this token, we may need
	 * to generate another one.
	 * 
	 * Please note that following enum is order-sensitive. State
	 * values greater or equal VERIFICATION_OK (100) mean that
	 * we are no longer waiting for the res.
	 */ 
	typedef enum { NO_TOKEN = 0, VERIFICATION_WAITING, VERIFICATION_OK = 100, VERIFICATION_FAILED } TokenVerificationStatus;

	/*
	 * Controls comminication on the serial port.
	 */
	class Api {
		public:
			Api(long serialSpeed);
			~Api();

			// Log to serial port
			void log(const __FlashStringHelper *);

			// Controller loop API
			void update();
		private:
			// 
			TokenVerificationStatus tokenVerificationStatus;

	};

}}

#endif /* API_H */

