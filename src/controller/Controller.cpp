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
	display(PIN_LCD_RS, PIN_LCD_RW, PIN_LCD_EN, PIN_LCD_D0, PIN_LCD_D1, PIN_LCD_D2, PIN_LCD_D3, PIN_LCD_BACKLIGHT) 
{
	// Init serial port
	Serial.begin(9600);
	while (!Serial);
	
	Serial.println(F("LOG: Initialized application controller."));
}

Controller::~Controller() {
	Serial.println(F("LOG: Quitting application."));
}

void Controller::update() {
	// Perfmor state timeout actions if required.
	if (state.isTimedOut()) {
		handleStateTimeout();
	}

	// If we're awaiting token, check if there is one available on
	// serial port.
	if (model::state::AWAITING_TOKEN == state && Serial.available() > 0) {
		handleTokenReceive();
	}

	// Update interface elements.
	buzzer.update();
	led.update();
	display.update();
}

void Controller::handleNewTokenRequest() {
	if (state.isProcessingRequest()) {
		// We cannot proccess two request at time. Notify
		// user about rejection by buzzer.
		buzzer.beep(view::status::buzzer::BUSY);
	} else {
		// We can generate new token. Start by changing application
		// state.
		state = model::state::TOKEN_REQUESTED;

		// Send token request by serial port.
		while (Serial.read() != -1); // Discard all incoming data left
		Serial.println(F("RQ TKN")); // Send request for new token

		// Update interface elements to indicate that something
		// is happening.
		led.enable();
		buzzer.beep(view::status::buzzer::SUCCESS);
		display.show(new view::display::message::Busy);
	}
}

void Controller::handleTokenReceive() {
	// Token is available on serial port. 
	// Go and get it.
	String token = Serial.readStringUntil('\n');
	state = model::state::TOKEN_READY;

	led.disable();
	buzzer.beep(view::status::buzzer::SUCCESS);
	display.show(new view::display::message::Token(token));
}

void Controller::handleStateTimeout() {
	if (model::state::TOKEN_REQUESTED == state) {
		// Progress bar on display is complete, we can
		// look for token on serial port now.
		state = model::state::AWAITING_TOKEN;
	} else if (state.isProcessingRequest()) {
		// Timeout occured during token genration. Show
		// timeout message.
		state = model::state::REQUEST_TIMEOUT;

		led.disable();
		buzzer.beep(view::status::buzzer::FAILURE);
		display.show(new view::display::message::Timeout);
	} else if (model::state::IDLE == state) {
		// We're now idle for some time and may put CPU into sleep mode.
		Serial.println(F("LOG: Going to sleep"));
		delay(100); // Serial port need some time to send data.
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_cpu();
		sleep_disable();
		Serial.println(F("LOG: Waking up"));
	} else {
		// Timeout occured after successfull token
		// request. Cleanup and go back to IDLE.
		state = model::state::IDLE;

		led.disable();
		display.clear();
	}
}
