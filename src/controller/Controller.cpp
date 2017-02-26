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

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "Controller.h"
#include "../config.h"
#include "../view/display/message/Busy.h"
#include "../view/display/message/Timeout.h"
#include "../view/display/message/Token.h"

Controller::Controller() : 
	led(PIN_SLED), 
	buzzer(PIN_BUZZER), 
	display(PIN_LCD_RS, PIN_LCD_RW, PIN_LCD_EN, PIN_LCD_D0, PIN_LCD_D1, PIN_LCD_D2, PIN_LCD_D3, PIN_LCD_BACKLIGHT),
	generator(PIN_ANALOG_UNPLUGGED),
	api(SERIAL_SPEED)
{
	api.log(F("Initialized application controller."));
}

Controller::~Controller() {
	api.log(F("Quitting application."));
}

void Controller::update() {
	// Perfmor state timeout action if required.
	if (state.isTimedOut()) {
		handleStateTimeout();
	}

	// If we're during token generation and token is ready.
	if (state.isProcessingRequest() && generator.isReady()) {
		handleTokenReady();
	}

	// Update interface elements.
	buzzer.update();
	led.update();
	display.update();
	
	generator.update();
	api.update();
}

void Controller::handleNewTokenRequest() {
	if (state.isProcessingRequest()) {
		// We cannot proccess two request at time. Notify
		// user about rejection by buzzer.
		buzzer.beep(view::status::buzzer::BUSY);
	} else {
		api.log(F("New token request received"));
		
		// We can generate new token. Start by changing application
		// state.
		state = model::state::TOKEN_REQUESTED;

		// Update interface elements to indicate that something
		// is happening.
		led.enable();
		buzzer.beep(view::status::buzzer::SUCCESS);
		display.show(new view::display::message::Busy);
		
		// Start generating token.
		api.clearTokenVerificationStatus();
		generator.start(TOKEN_LENGTH);
		
	}
}

void Controller::handleTokenReady() {
	// Token is ready. Now we need to send it to controlling
	// unit and wait for response.
	
	if(!api.isTokenSent()) {
		// Send token to controlling unit.
		api.sendVerifyToken(generator.getToken());
	} else if(api.isTokenRejected()) {
		// Token was rejected, restart generation.
		api.clearTokenVerificationStatus();
		generator.start(TOKEN_LENGTH);
		
		api.log(F("Token was rejected - restarting generator"));
	} else if(api.isTokenAccepted() && model::state::AWAITING_CONFIRMATION == state) {
		// Token was accepted and we're now ready to display it.
		state = model::state::TOKEN_ACCEPTED;
		
		led.disable();
		buzzer.beep(view::status::buzzer::SUCCESS);
		display.show(new view::display::message::Token(generator.getToken()));
		
		api.log(F("Token was accepted and displayed on the screen"));
	}
}

void Controller::handleStateTimeout() {
	if (model::state::TOKEN_REQUESTED == state) {
		// Progress bar on display is complete, we can
		// display token if it's ready.
		state = model::state::AWAITING_CONFIRMATION;
	} else if (state.isProcessingRequest()) {
		// Timeout occured during token genration. Show
		// timeout message.
		state = model::state::REQUEST_TIMEOUT;

		led.disable();
		buzzer.beep(view::status::buzzer::FAILURE);
		display.show(new view::display::message::Timeout);
		
		// Ignore late responses from controlling unit.
		api.clearTokenVerificationStatus();
	} else if (model::state::IDLE == state) {
		// We're now idle for some time and may put CPU into sleep mode.
		api.log(F("Going to sleep"));
		delay(100); // Serial port API need some time to send data.
		
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_cpu();
		sleep_disable();
		
		api.log(F("Waking up"));
	} else {
		// Final message is now displayed for some time 
		// and we may hide it and go back to IDLE.
		state = model::state::IDLE;
		display.clear();
	}
}
