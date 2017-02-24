#include "Token.h"
using namespace view::display::message;

Token::Token(const String & token): Message(), token(token) { }
Token::~Token() { }

LiquidCrystal & Token::printOn(LiquidCrystal & lcd) {
	lcd.setCursor(0, 0);
	lcd.print(msg);

	lcd.setCursor((16 - token.length()) / 2, 1);
	lcd.print(token);

	return lcd;
}
