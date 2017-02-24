/*
 * Message.h
 *
 *  Created on: 22.02.2017
 *      Author: patryk
 *
 * Base class responsible for displaying messages
 * on LCD screen.
 */

#ifndef SRC_VIEW_DISPLAY_MESSAGE_H_
#define SRC_VIEW_DISPLAY_MESSAGE_H_

#include <LiquidCrystal.h>

namespace view { namespace display {
	class Message {
		public:
			Message();
			virtual ~Message();
			virtual LiquidCrystal & printOn(LiquidCrystal & lcd) = 0;
			virtual LiquidCrystal & updateOn(LiquidCrystal & lcd);
		};
}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_H_ */
