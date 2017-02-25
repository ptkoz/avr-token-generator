/*
 * UI.cpp
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 */

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "Controller.h"
#include "../view/display/message/Busy.h"
#include "../view/display/message/Timeout.h"
#include "../view/display/message/Token.h"

Controller::Controller(): led(13), buzzer(4), display(6, 7, 8, 9, 10, 11, 12, 5) { }
Controller::~Controller() { }

void Controller::update() {
	if(state.isTimedOut()) {
		handleStateTimeout();
	}

	if(model::state::AWAITING_TOKEN == state && Serial.available() > 0) {
		handleTokenReceive();
	}

	buzzer.update();
	led.update();
	display.update();
}

void Controller::handleNewTokenRequest() {
	if(state.isProcessingRequest()) {
		buzzer.beep(view::status::buzzer::BUSY);
	} else {
		state = model::state::TOKEN_REQUESTED;

		while(Serial.read() != -1); // discard all incoming data left
		Serial.print(F("RQ TKN\n")); // send request for new token

		led.enable();
		buzzer.beep(view::status::buzzer::SUCCESS);
		display.show(new view::display::message::Busy);
	}
}

void Controller::handleTokenReceive() {
	String token = Serial.readStringUntil('\n');
	state = model::state::TOKEN_READY;

	led.disable();
	buzzer.beep(view::status::buzzer::SUCCESS);
	display.show(new view::display::message::Token(token));
}

void Controller::handleStateTimeout() {
	if(model::state::TOKEN_REQUESTED == state) {
		/**
		 * This is very special state that must time-out
		 * every time. This is required to show whole progress
		 * bar. Simply go to next state.
		 */
		state = model::state::AWAITING_TOKEN;
	} else if(state.isProcessingRequest()) {
		/**
		 * Timeout occured during token genration. Show
		 * timeout message.
		 */
		state = model::state::REQUEST_TIMEOUT;

		led.disable();
		buzzer.beep(view::status::buzzer::FAILURE);
		display.show(new view::display::message::Timeout);
	} else if(model::state::IDLE == state) {
		/**
		 * Idle state lasted for 10 seconds, go to sleep.
		 */
		Serial.print(F("Going to sleep\n"));
		delay(100);
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_cpu();
		sleep_disable();
		Serial.print(F("Waking up\n"));
	} else {
		/**
		 * Timeout occured after successfull token
		 * request. Cleanup and go back to IDLE.
		 */
		state = model::state::IDLE;

		led.disable();
		display.clear();
	}
}
