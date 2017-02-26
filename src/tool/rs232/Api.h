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
	 * values greater or equal VERIFICATION_WAITING mean that token 
	 * have been sent to controlling unit.
	 */ 
	typedef enum { NO_TOKEN = 0, VERIFICATION_WAITING = 100, VERIFICATION_OK, VERIFICATION_FAILED } TokenVerificationStatus;

	/*
	 * Controls comminication on the serial port.
	 */
	class Api {
		public:
			Api(long);
			~Api();

			// Log to serial port
			void log(const __FlashStringHelper *);
			
			// Send token to controlling unit and await verification.
			void sendVerifyToken(const char * token);
			// We don't care about last sent token, reset back to NO_TOKEN.
			void clearTokenVerificationStatus();
			
			// Have token been sent to controlling unit yet?
			bool isTokenSent() { return VERIFICATION_WAITING <= tokenVerificationStatus; }
			// Have controlling unit accepted token?
			bool isTokenAccepted() { return VERIFICATION_OK == tokenVerificationStatus; } 
			// Have controlling unit responded about token yet?
			bool isTokenRejected() { return VERIFICATION_FAILED == tokenVerificationStatus; }

			// Controller loop API
			void update();
		private:
			TokenVerificationStatus tokenVerificationStatus;

	};

}}

#endif /* API_H */

