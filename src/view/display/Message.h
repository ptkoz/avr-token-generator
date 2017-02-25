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

#ifndef SRC_VIEW_DISPLAY_MESSAGE_H_
#define SRC_VIEW_DISPLAY_MESSAGE_H_

#include <LiquidCrystal.h>

namespace view { namespace display {
	/*
	 * Class that represents single message displayed
	 * on the LCD screen.
	 */
	class Message {
		public:
			Message();
			virtual ~Message();
			
			// Method responsible for displaying the message.
			virtual LiquidCrystal & printOn(LiquidCrystal & lcd) = 0;
			
			// Method called on each iteration of application loop.
			// By default does nothing, but if you want dynamic message
			// (eg. progress bar) you may update it by overloading
			// this method.
			virtual LiquidCrystal & updateOn(LiquidCrystal & lcd);
		};
}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_H_ */
