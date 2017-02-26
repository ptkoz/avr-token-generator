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

#include "Api.h"

using namespace tool::rs232;

Api::Api(long serialSpeed) { 
	Serial.begin(serialSpeed); // initialize serial port
	while (!Serial);
}

Api::~Api() {
	Serial.end();
}

void Api::log(const __FlashStringHelper * message) {
	Serial.print(F("LOG:"));
	Serial.print(message);
	Serial.write('\n');
}

void Api::sendVerifyToken(const char * token) {
	tokenVerificationStatus = VERIFICATION_WAITING;
	
	// Clear any data left on serial port.
	while(Serial.available() > 0) Serial.read();
	
	// Send new token.
	Serial.print(F("TKN:"));
	Serial.write(token);
	Serial.write('\n');
}

void Api::clearTokenVerificationStatus() {
	tokenVerificationStatus = NO_TOKEN;
}


void Api::update() {
	// If we expecting token verification response and there is data on serial
	if(VERIFICATION_WAITING == tokenVerificationStatus && Serial.available() > 0) {
		String response = Serial.readStringUntil('\n');
		tokenVerificationStatus = (response == "OK") ? VERIFICATION_OK : VERIFICATION_FAILED;
	}
}