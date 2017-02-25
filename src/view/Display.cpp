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
	clearMessage(); // Free memory allocated by the message.
}

void Display::update() {
	// If there is any message displayed, maybe it want 
	// to be updated?
	if(currentMessage) {
		currentMessage->updateOn(screen);
	}
}

void Display::show(Message * newMessage) {
	// Clear any previous message.
	screen.clear();
	// Cleanup memory after previous message.
	clearMessage();

	// Give message screen it may be displayed on.
	currentMessage = newMessage;
	currentMessage->printOn(screen);

	// Enable backligjt if disabled.
	if(!backlight.getCurrentState()) {
		backlight.enable();
	}
}

void Display::clear() {
	backlight.disable();

	screen.clear(); // Clear the screen.
	clearMessage();  // Free the memory.
}

void Display::clearMessage() {
	if(NULL != currentMessage) {
		delete currentMessage;
		currentMessage = NULL;
	}
}
