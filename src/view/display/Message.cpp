#include "Message.h"

using namespace view::display;

Message::Message() { }

Message::~Message() { }

LiquidCrystal & Message::updateOn(LiquidCrystal & lcd) { return lcd; }
