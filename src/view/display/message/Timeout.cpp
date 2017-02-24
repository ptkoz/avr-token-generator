#include "Timeout.h"
using namespace view::display::message;

Timeout::Timeout(): Message() { }
Timeout::~Timeout() { }

LiquidCrystal & Timeout::printOn(LiquidCrystal & lcd) {
	lcd.setCursor(0, 0);
	lcd.print(line1);

	lcd.setCursor(0, 1);
	lcd.print(line2);

	return lcd;
}
