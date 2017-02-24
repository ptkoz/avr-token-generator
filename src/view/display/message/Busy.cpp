#include "Arduino.h"
#include "Busy.h"
using namespace view::display::message;

Busy::Busy(): Message(), lastProgressStep(0), progressStepsLeft(16) { }
Busy::~Busy() { }

LiquidCrystal & Busy::printOn(LiquidCrystal & lcd) {
	lcd.setCursor(0, 0);
	lcd.print(msg);
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
