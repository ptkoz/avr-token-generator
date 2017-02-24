/*
 * Display.cpp
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 */

#include "Display.h"
using namespace view::display;

Display::Display(const char rs, const char rw, const char enable, const char d0, const char d1, const char d2, const char d3, const char backlight):
	screen(rs, rw, enable, d0, d1, d2, d3),
	backlight(backlight),
	currentMessage(NULL)
{
	screen.begin(16, 2);
}

Display::~Display() {
	clearMessage();
}

void Display::update() {
	if(currentMessage) {
		currentMessage->updateOn(screen);
	}
}

void Display::show(Message * newMessage) {
	screen.clear();
	clearMessage();

	currentMessage = newMessage;
	currentMessage->printOn(screen);

	if(!backlight.getCurrentState()) {
		backlight.enable();
	}
}

void Display::clear() {
	backlight.disable();

	screen.clear();
	clearMessage();
}

void Display::clearMessage() {
	if(NULL != currentMessage) {
		delete currentMessage;
		currentMessage = NULL;
	}
}
