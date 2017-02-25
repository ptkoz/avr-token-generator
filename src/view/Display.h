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

#ifndef SRC_VIEW_DISPLAY_H_
#define SRC_VIEW_DISPLAY_H_

#include <LiquidCrystal.h>
#include "../tool/pin/digital/Output.h"
#include "display/Message.h"

namespace view { namespace display {
	class Display {
		public:
			Display(const char rs, const char rw, const char enable, const char d0, const char d1, const char d2, const char d3, const char backlight);
			~Display();

			// API for controller loop
			void update();

			void show(Message * msg);
			void clear();
		private:
			void clearMessage();

			LiquidCrystal screen;
			tool::pin::digital::Output backlight;
			Message * currentMessage;

	};
}}

#endif /* SRC_VIEW_DISPLAY_H_ */
