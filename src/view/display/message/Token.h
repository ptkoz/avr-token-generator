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

#ifndef SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_
#define SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_

#include "../Message.h"

namespace view { namespace display { namespace message {

/*
 * Message displaying generated token on
 * the LCD screen.
 */
class Token: public Message {
	public:
		Token(const String & token);
		~Token();

		LiquidCrystal & printOn(LiquidCrystal & lcd);
	private:
		// The token message caption.
		const String msg = "Twoj token WiFi:";
		// The token to display.
		const String token;
};

}}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_ */
