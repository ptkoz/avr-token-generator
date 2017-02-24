/*
 * Display.h
 *
 *  Created on: 21.02.2017
 *      Author: patryk
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
