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

#include "Arduino.h"
#include "Busy.h"
using namespace view::display::message;

Busy::Busy(): Message(), lastProgressStep(0), progressStepsLeft(16) { }
Busy::~Busy() { }

LiquidCrystal & Busy::printOn(LiquidCrystal & lcd) {
	lcd.setCursor(0, 0);
	lcd.print(msg);
	
	// Progress bar is displayed in second line.
	lcd.setCursor(0, 1);
	return lcd;
}

LiquidCrystal & Busy::updateOn(LiquidCrystal & lcd) {
	unsigned long timeNow = millis();
	if(timeNow - lastProgressStep > PROGRESS_STEP_DURATION && progressStepsLeft > 0) {
		lcd.print(PROGRESS_CHAR);
		lastProgressStep = timeNow;
		progressStepsLeft--;
	}
	return lcd;
}
