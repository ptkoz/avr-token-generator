/*
 * Busy.h
 *
 *  Created on: 22.02.2017
 *      Author: patryk
 *
 *  Message displayed when token is generating.
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
