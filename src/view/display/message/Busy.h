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

#ifndef SRC_VIEW_DISPLAY_MESSAGE_BUSY_H_
#define SRC_VIEW_DISPLAY_MESSAGE_BUSY_H_

#include "../Message.h"

namespace view { namespace display { namespace message {

// handy constant
const char PROGRESS_CHAR = char(255);
const unsigned short PROGRESS_STEP_DURATION = 100;

class Busy: public Message {
	public:
		Busy();
		~Busy();

		LiquidCrystal & printOn(LiquidCrystal & lcd);
		LiquidCrystal & updateOn(LiquidCrystal & lcd);
	private:
		String msg = "Generuje token";
		unsigned long lastProgressStep;
		unsigned char progressStepsLeft;

};

}}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_BUSY_H_ */
